/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:08:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/29 23:15:55 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_argv_values(char **argv)
{
	t_info info;

	info.number_of_philos = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info.maximum_eat_count = ft_atoi(argv[5]);
}

unsigned long long get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*is_what(void *arg, char *str)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	printf("%llu %d is %s\n", get_current_time_in_ms(), philo.number, str);
}



int	main(int argc, char **argv)
{
	if (argc_validation(argc) || input_validation(argv) || validate_int_limits(argv))
		return (1);
	assign_argv_values(argv);
	return (0);
}

//n die eat sleep cycle_count