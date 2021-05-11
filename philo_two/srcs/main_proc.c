/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:23:37 by bswag             #+#    #+#             */
/*   Updated: 2021/05/11 22:27:42 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
	sem_wait(p->table->s_output);
	printf("%lli %i %s\n", cur_time / 1000, p->num, str);
	sem_post(p->table->s_output);
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
