/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:05:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 21:56:37 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_end_of_simulation_value(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->info->printf_mutex);
	res = philo->info->end_simulation == 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (res);
}

unsigned long long	get_last_eat_time(t_philo *philo)
{
	unsigned long long	res;

	pthread_mutex_lock(&philo->info->printf_mutex);
	res = philo->last_eat_time;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (res);	
}
