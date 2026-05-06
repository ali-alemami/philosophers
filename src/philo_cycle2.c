/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:03:33 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 22:35:25 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo *philo)
{
	unsigned long long	t;

	t = get_current_time_in_ms();
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (!philo->info->end_simulation)
	{
		printf("%llu %d is eating\n", t, philo->number);
		philo->last_eat_time = t;
		philo->eat_count++;
	}
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (!philo->info->end_simulation)
		printf("%llu %d is sleeping\n", get_current_time_in_ms(), philo->number);
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (!philo->info->end_simulation)
		printf("%llu %d is thinking\n", get_current_time_in_ms(), philo->number);
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

void	*kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d died\n", get_current_time_in_ms(), philo->number);
	philo->info->end_simulation = 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (NULL);
}
