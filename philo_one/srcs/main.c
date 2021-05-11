/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:02:38 by bswag             #+#    #+#             */
/*   Updated: 2021/05/11 22:19:58 by bswag            ###   ########.fr       */
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
