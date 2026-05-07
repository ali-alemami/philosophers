/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:05:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 15:23:55 by aalemami         ###   ########.fr       */
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

int	philo_eat_count(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->info->printf_mutex);
	res = philo->eat_count >= philo->info->maximum_eat_count;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (res);
}

void	*end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	philo->info->end_simulation = 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (NULL);
}

int	is_philo_dead(t_philo *philo)
{
	unsigned long long	current_time;
	unsigned long long	last_eat;

	pthread_mutex_lock(&philo->info->printf_mutex);
	current_time = get_current_time_in_ms();
	last_eat = philo->last_eat_time;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (current_time >= last_eat + philo->info->time_to_die);
}
