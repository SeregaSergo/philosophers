/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:26:57 by bswag             #+#    #+#             */
/*   Updated: 2021/05/12 01:16:47 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

# define COMPLITED	0
# define DEAD		1

typedef struct s_phil	t_phil;

typedef struct s_table
{
	int				num_phil;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_meals;
	t_phil			*phils;
	sem_t			*s_forks;
	sem_t			*s_output;
	sem_t			*s_queue;
}					t_table;

typedef struct s_phil
{
	int				num;
	pid_t			pid;
	t_table			*table;
	long long int	time_last;
	int				num_meals;
}					t_phil;

long long int	ft_atoi_long(const char *str);
int				check_if_args_are_pos_numbers(char **argv);
int				check_if_args_are_integers(char **argv);
void			get_time_ms(long long int *time_last);
void			print_to_output(t_phil *p, char *str);
int				life_cycle(t_phil *p);
void			set_the_table(t_table *table);
int				error_msg(char *str);

#endif
