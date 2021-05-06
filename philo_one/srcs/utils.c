/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:35:08 by bswag             #+#    #+#             */
/*   Updated: 2021/05/06 18:02:20 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

long long int	ft_atoi_long(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	result = 0;
	sign = 1;
	i = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (c);
	else
		return (0);
}

int	is_pos_number(char *arg)
{
	if (*arg == '-')
		return (1);
	if (*arg == '+')
		arg++;
	while (*arg != '\0')
	{
		if (!ft_isdigit(*arg))
			return (1);
		arg++;
	}
	return (0);
}

int	check_if_args_are_pos_numbers(char **argv)
{
	while (*argv)
	{
		if (is_pos_number(*argv))
			return (1);
		argv++;
	}
	return (0);
}

int	check_if_args_are_integers(char **argv)
{
	long long int	ret;
	int				i;

	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if (i > 11)
				return (1);
			i++;
		}
		ret = ft_atoi_long(*argv);
		if (ret > INT_MAX || ret < INT_MIN)
			return (1);
		argv++;
	}
	return (0);
}
