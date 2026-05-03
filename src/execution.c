/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:38:42 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/03 00:33:25 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	execution(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
		pthread_mutex_lock(&philo->next->fork);
		printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
		is_eating(philo);
		is_sleeping(philo);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo = philo->next;
		i++;
	}
}

	// philo1 take fork1 take fork2  starts eating philo2 sees fork busy w8 until phil1 finishes eating and goes to sleep then he takes the fork and starts eating
