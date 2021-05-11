/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:02:38 by bswag             #+#    #+#             */
/*   Updated: 2021/05/11 22:27:21 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
	sem_unlink("/forks");
	sem_unlink("/output");
	sem_unlink("/queue");
	table->s_forks = sem_open("/forks", O_CREAT, 0660, table->num_phil);
	table->s_output = sem_open("/output", O_CREAT, 0660, 1);
	table->s_queue = sem_open("/queue", O_CREAT, 0660, 1);
	if (!table->phils || table->s_forks == SEM_FAILED || table->s_output == \
	SEM_FAILED || table->s_queue == SEM_FAILED)
		return (error_msg("memory allocation failure"));
	while (i < table->num_phil)
	{
		table->phils[i].table = table;
		table->phils[i].num = i + 1;
		table->phils[i].status = IN_PROCESS;
		table->phils[i].num_meals = table->num_meals;
		i++;
	}
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
	free(table.phils);
	sem_unlink("/forks");
	sem_unlink("/output");
	sem_unlink("/queue");
	return (0);
}
