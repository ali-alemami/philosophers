/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:47:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/03 20:07:19 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taken_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
	if (philo->status == INITIALIZED || philo->status == IS_THINKING)
		philo->status = HAS_ONE_FORK;
	else if (philo->status == HAS_ONE_FORK)
		philo->status = HAS_TWO_FORKS;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

void	is_eating(t_philo *philo)
{
	philo->last_eat_time = get_current_time_in_ms();
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d is eating\n", get_current_time_in_ms(), philo->number);
	philo->status = IS_EATING;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_eat);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d is sleeping\n", get_current_time_in_ms(), philo->number);
	philo->status = IS_SLEEPING;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_sleep);
}

void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %s died\n", get_current_time_in_ms(), philo->number);
	philo->status = DEAD;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}
