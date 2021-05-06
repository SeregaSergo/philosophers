/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:59:43 by bswag             #+#    #+#             */
/*   Updated: 2021/05/06 19:01:41 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <limits.h>
#include <stdio.h>
#include <pthread.h>

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
	pthread_t		thread;
	t_table			*table;
}					t_phil;

long long int	ft_atoi_long(const char *str);
int 			check_if_args_are_pos_numbers(char **argv);
int 			check_if_args_are_integers(char **argv);

#endif
