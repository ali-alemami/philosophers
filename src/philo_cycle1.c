/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:47:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 15:37:40 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*get_first_fork(t_philo *philo)
{
	if (&philo->fork < &philo->next->fork)
		return (&philo->fork);
	else if (&philo->fork > &philo->next->fork)
		return (&philo->next->fork);
	return (&philo->fork);
}

pthread_mutex_t	*get_second_fork(t_philo *philo)
{
	if (&philo->fork > &philo->next->fork)
		return (&philo->fork);
	else if (&philo->fork < &philo->next->fork)
		return (&philo->next->fork);
	return (&philo->next->fork);
}

int	take_first_fork(t_philo *philo)
{
	pthread_mutex_lock(get_first_fork(philo));
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (philo->info->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->info->printf_mutex);
		pthread_mutex_unlock(get_first_fork(philo));
		return (0);
	}
	printf("%llu %d has taken a fork\n",
		get_timestamp(philo), philo->number + 1);
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (1);
}

int	take_second_fork(t_philo *philo)
{
	pthread_mutex_lock(get_second_fork(philo));
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (philo->info->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->info->printf_mutex);
		pthread_mutex_unlock(get_first_fork(philo));
		pthread_mutex_unlock(get_second_fork(philo));
		return (0);
	}
	printf("%llu %d has taken a fork\n",
		get_timestamp(philo), philo->number + 1);
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (1);
}
