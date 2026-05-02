/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 03:13:44 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/02 13:36:31 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	argc_validation(int argc)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		ft_putstr_fd("Usage: ./philo [number_of_philosophers] ", 2);
		ft_putstr_fd("[time_to_die] [time_to_eat] [time_to_sleep]\n", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat] (optinal argument)\n", 2);
		return (1);
	}
	return (0);
}

static int	input_validation(char **argv)
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

static int	get_len(char *str)
{
	int	len;
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	len = 0;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
}

static int	validate_int_limits(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (get_len(argv[i]) < 10)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(argv[i], "2147483647", 11) > 0)
		{
			ft_putstr_fd("Error: the input exceeds the int limit\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_all_args(char argc, char **argv)
{
	if (argc_validation(argc) || input_validation(argv) || validate_int_limits(argv))
		return (1);
	return (0);
}