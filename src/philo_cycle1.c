/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:47:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 22:54:51 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (philo->info->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->info->printf_mutex);
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

void	take_second_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (philo->info->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->info->printf_mutex);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return ;
	}
	printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
	pthread_mutex_unlock(&philo->info->printf_mutex);
}
