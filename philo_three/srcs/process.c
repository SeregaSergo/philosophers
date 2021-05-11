/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:23:46 by bswag             #+#    #+#             */
/*   Updated: 2021/05/12 01:15:04 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	is_phil_dead(t_phil *p)
{
	long long int	cur_time;

	get_time_ms(&cur_time);
	if ((cur_time - p->time_last) > p->table->t_die * 1000)
	{
		sem_wait(p->table->s_output);
		printf("%lli %i died\n", cur_time / 1000, p->num);
		exit(DEAD);
	}
}

void	eating(t_phil *p)
{
	sem_wait(p->table->s_queue);
	sem_wait(p->table->s_forks);
	sem_wait(p->table->s_forks);
	sem_post(p->table->s_queue);
	print_to_output(p, "has taken a fork");
	print_to_output(p, "is eating");
	get_time_ms(&p->time_last);
	if (p->table->t_die > p->table->t_eat)
		usleep(p->table->t_eat * 1000);
	else
	{
		usleep(p->table->t_die * 1000);
		is_phil_dead(p);
	}
	sem_post(p->table->s_forks);
	sem_post(p->table->s_forks);
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
	}
	else
	{
		usleep(time);
		is_phil_dead(p);
	}
	return (1);
}

int	life_cycle(t_phil *phil)
{
	get_time_ms(&phil->time_last);
	while (phil->num_meals == -1 || phil->num_meals > 0)
	{
		is_phil_dead(phil);
		eating(phil);
		sleeping_thinking(phil);
		if (phil->num_meals > 0)
			phil->num_meals--;
	}
	exit(COMPLITED);
}
