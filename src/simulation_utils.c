/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:47:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/04 21:09:16 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (philo->status == DEAD)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
	philo->status = HAS_ONE_FORK;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

void	take_second_fork(t_philo *philo)
{
	if (philo->status == DEAD)
		return ;
	pthread_mutex_lock(&philo->next->fork);
	if (philo->status == DEAD)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return ;
	}
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d has taken a fork\n", get_current_time_in_ms(), philo->number);
	philo->status = HAS_TWO_FORKS;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

void	is_eating(t_philo *philo)
{
	if (philo->status == DEAD)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return ;
	}
	philo->last_eat_time = get_current_time_in_ms();
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d is eating\n", get_current_time_in_ms(), philo->number);
	philo->status = IS_EATING;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	is_sleeping(t_philo *philo)
{
	if (philo->status == DEAD)
		return ;
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d is sleeping\n", get_current_time_in_ms(), philo->number);
	philo->status = IS_SLEEPING;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	if (philo->status == DEAD)
		return ;
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d is thinking\n", get_current_time_in_ms(), philo->number);
	philo->status = IS_THINKING;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d died\n", get_current_time_in_ms(), philo->number);
	philo->status = DEAD;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}
