/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:59:43 by bswag             #+#    #+#             */
/*   Updated: 2021/05/11 22:22:02 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define IN_PROCESS	0
# define COMPLITED	1
# define DEAD		2

typedef struct s_phil	t_phil;

typedef struct s_table
{
	int				num_phil;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_meals;
	t_phil			*phils;
	pthread_mutex_t	mtx_output;
	pthread_mutex_t	*mtx_forks;
}					t_table;

typedef struct s_phil
{
	int				num;
	pthread_t		thread;
	t_table			*table;
	long long int	time_last;
	int				num_meals;
	int				status;
}					t_phil;

long long int	ft_atoi_long(const char *str);
int				check_if_args_are_pos_numbers(char **argv);
int				check_if_args_are_integers(char **argv);
void			*life_cycle(void *p);
void			set_the_table(t_table *table);
void			get_time_ms(long long int *time_last);
void			print_to_output(t_phil *p, char *str);

#endif
