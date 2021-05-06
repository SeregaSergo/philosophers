/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:02:38 by bswag             #+#    #+#             */
/*   Updated: 2021/05/06 18:03:24 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	error_msg(char *str)
{
	printf("ERROR: %s\n", str);
	return (1);
}

int	check_input_init(int argc, char **argv, t_table *table)
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

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_input_init(argc, argv, &table))
		return (1);
	return (0);
}
