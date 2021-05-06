/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:01:49 by bswag             #+#    #+#             */
/*   Updated: 2021/05/06 18:03:53 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

#include <limits.h>
#include <stdio.h>

typedef struct s_table
{
	int			num_phil;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			num_meals;
}				t_table;

long long int	ft_atoi_long(const char *str);
int 			check_if_args_are_pos_numbers(char **argv);
int 			check_if_args_are_integers(char **argv);

#endif
