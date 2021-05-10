/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:02:38 by bswag             #+#    #+#             */
/*   Updated: 2021/05/11 02:44:35 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	error_msg(char *str)
{
	printf("ERROR: %s\n", str);
	return (1);
}

int	check_input(int argc, char **argv, t_table *table)
{
	if (argc < 5)
		return (error_msg("not enough arguments"));
	if (argc > 6)
		return (error_msg("too many arguments"));
	if (check_if_args_are_pos_numbers(&argv[1]))
		return (error_msg("arguments can only be positive numbers"));
	if (check_if_args_are_integers(&argv[1]))
		return (error_msg("arguments can only be integergs"));
	table->num_phil = (int)ft_atoi_long(argv[1]);
	table->t_die = (int)ft_atoi_long(argv[2]);
	table->t_eat = (int)ft_atoi_long(argv[3]);
	table->t_sleep = (int)ft_atoi_long(argv[4]);
	if (argc == 6)
		table->num_meals = (int)ft_atoi_long(argv[5]);
	else
		table->num_meals = -1;
	if (table->num_phil == 0)
		return (error_msg("it seems that there are no philosophers \
left in this world :("));
	return (0);
}

int	init_main_structure(t_table *table)
{
	int	i;

	i = 0;
	table->phils = (t_phil *)malloc(table->num_phil * sizeof(t_phil));
	table->mtx_forks = (pthread_mutex_t *)malloc(table->num_phil * \
	sizeof(pthread_mutex_t));
	if (!table->phils || !table->mtx_forks)
		return (error_msg("memory allocation failure"));
	while (i < table->num_phil)
	{
		// init data in t_phil structure
		table->phils[i].table = table;
		table->phils[i].num = i + 1;
		table->phils[i].status = IN_PROCESS;
		table->phils[i].num_meals = table->num_meals;
		pthread_mutex_init(&table->mtx_forks[i], 0);
		i++;
	}
	pthread_mutex_init(&table->mtx_output, 0);
	return (0);
}

void	get_time_ms(long long int *time_last)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	*time_last = time.tv_sec * 1000000 + time.tv_usec;
}

void	print_to_output(t_phil *p, char *str)
{
	long long int	cur_time;

	get_time_ms(&cur_time);
	pthread_mutex_lock(&p->table->mtx_output);
	printf("%lli %i %s\n", cur_time / 1000, p->num, str);
	pthread_mutex_unlock(&p->table->mtx_output);
}

int	is_phil_dead(t_phil *p)
{
	long long int	cur_time;

	get_time_ms(&cur_time);
	if ((cur_time - p->time_last) > p->table->t_die * 1000)
	{
		pthread_mutex_lock(&p->table->mtx_output);
		printf("%lli %i died\n", cur_time / 1000, p->num);
		p->status = DEAD;
		return (1);
	}
	return (0);
}

int	left_fork(t_phil *p)
{
	if (p->num == 1)
		return (p->table->num_phil - 1);
	else
		return (p->num - 2);
}

int	eating(t_phil *p)
{
	pthread_mutex_lock(&p->table->mtx_forks[left_fork(p)]);
	pthread_mutex_lock(&p->table->mtx_forks[p->num - 1]);
	print_to_output(p, "has taken a fork");
	print_to_output(p, "is eating");
	get_time_ms(&p->time_last);
	if (p->table->t_die > p->table->t_eat)
		usleep(p->table->t_eat * 1000);
	else
	{
		usleep(p->table->t_die * 1000);
		return (1);
	}
	pthread_mutex_unlock(&p->table->mtx_forks[left_fork(p)]);
	pthread_mutex_unlock(&p->table->mtx_forks[p->num - 1]);
	return (0);
}

int	sleeping_thinking(t_phil *p)
{
	long long int	time;

	print_to_output(p, "is sleeping");
	get_time_ms(&time);
	time = p->table->t_die * 1000 - (time - p->time_last);
	if (time < 0)
		time = 0;
	if (time > p->table->t_sleep * 1000)
	{
		usleep(p->table->t_sleep * 1000);
		print_to_output(p, "is thinking");
		return (0);
	}
	else
		usleep(time);
	return (1);
}

void	*life_cycle(void *p)
{
	t_phil	*phil;

	phil = (t_phil *)p;
	get_time_ms(&phil->time_last);
	while (phil->num_meals == -1 || phil->num_meals > 0)
	{
		if (is_phil_dead(phil))
			return (NULL);
		if (eating(phil))
		{
			is_phil_dead(phil);
			return (NULL);
		}
		if (sleeping_thinking(phil))
		{
			is_phil_dead(phil);
			return (NULL);
		}
		if (phil->num_meals > 0)
			phil->num_meals--;
	}
	phil->status = COMPLITED;
	return (NULL);
}

int	died_or_complited(t_phil *phils, int n)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (i < n)
	{
		if (phils[i].status == DEAD)
			return (1);
		else if (phils[i].status == COMPLITED)
			count++;
		i++;
	}
	if (count == n)
		return (1);
	return (0);
}

void	set_the_table(t_table *table)
{
	int		i;
	t_phil	*phils;
	
	i = 0;
	phils = table->phils;
	while (i < table->num_phil)
	{
		get_time_ms(&phils[i].time_last);
		pthread_create(&(phils[i].thread), 0, life_cycle, &(phils[i]));
		pthread_detach(table->phils[i].thread);
		i++;
	}
	while (!died_or_complited(table->phils, table->num_phil))
		usleep(table->t_die * 1000 / 2);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_input(argc, argv, &table))
		return (1);
	if (init_main_structure(&table))
		return (1);
	set_the_table(&table);
	free(table.mtx_forks);
	free(table.phils);
	return (0);
}
