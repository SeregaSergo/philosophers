/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:23:37 by bswag             #+#    #+#             */
/*   Updated: 2021/05/12 01:17:13 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

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

void	wait_children_proc(t_table *table)
{
	int	status;
	int	i;

	i = 0;
	while (i < table->num_phil)
	{
		waitpid(0, &status, 0);
		if (status == DEAD)
			kill(0, SIGKILL);
		i++;
	}
}

void	fork_error_exit(int i, t_table *table)
{
	int	status;

	while (i > -1)
	{
		kill(table->phils[i].pid, SIGKILL);
		waitpid(table->phils[i].pid, &status, 0);
		i--;
	}
	sem_unlink("/forks");
	sem_unlink("/output");
	sem_unlink("/queue");
	exit(error_msg("can't create fork"));
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
		table->phils[i].pid = fork();
		if (table->phils[i].pid == 0)
			life_cycle(&table->phils[i]);
		else if (table->phils[i].pid < 0)
			fork_error_exit(i - 1, table);
		i++;
	}
	wait_children_proc(table);
}
