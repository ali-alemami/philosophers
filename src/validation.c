/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 03:13:44 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/29 03:14:16 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argc_validation(int argc)
{
	if (argc != 6 || argc != 7)
	{
		ft_putstr_fd("Error: missing arguments\n", 2);
		ft_putstr_fd("Usage: ./philo number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep", 2);
		ft_putstr_fd("number_of_times_each_philosopher_must_eat (optinal argument)\n", 2);
		return (1);
	}
	return (0);
}

int	input_validation(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i]))
		{
			ft_putstr_fd("Error: non integer or negative values\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_int_limits(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "2147483647", 11) > 0)
		{
			ft_putstr_fd("Error: the input exceeds the int limit\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
