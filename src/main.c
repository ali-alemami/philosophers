/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:08:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/30 12:53:27 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
	pthread_mutex_lock(philo.fork);
	printf("%llu %d is %s\n", get_current_time_in_ms(), philo.number, str);
}

void	execution(t_philo *philos)
{
	
}


int	main(int argc, char **argv)
{
	if (argc_validation(argc) || input_validation(argv) || validate_int_limits(argv))
		return (1);
	assign_argv_values(argv);
	return (0);
}

//n die eat sleep cycle_count