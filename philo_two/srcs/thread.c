/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:23:46 by bswag             #+#    #+#             */
/*   Updated: 2021/05/11 22:24:43 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	is_phil_dead(t_phil *p)
{
	long long int	cur_time;

	get_time_ms(&cur_time);
	if ((cur_time - p->time_last) > p->table->t_die * 1000)
	{
		sem_wait(p->table->s_output);
		printf("%lli %i died\n", cur_time / 1000, p->num);
		p->status = DEAD;
		return (1);
	}
	return (0);
}

int	eating(t_phil *p)
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
		return (1);
	}
	sem_post(p->table->s_forks);
	sem_post(p->table->s_forks);
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
