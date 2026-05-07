/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:03:33 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 15:59:20 by aalemami         ###   ########.fr       */
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
		printf("%llu %d is eating\n", t, philo->number + 1);
		philo->last_eat_time = t;
		philo->eat_count++;
	}
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(get_first_fork(philo));
	pthread_mutex_unlock(get_second_fork(philo));
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (!philo->info->end_simulation)
		printf("%llu %d is sleeping\n",
			get_current_time_in_ms(), philo->number + 1);
	pthread_mutex_unlock(&philo->info->printf_mutex);
	ft_usleep(philo->info->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	long long	think_time;

	pthread_mutex_lock(&philo->info->printf_mutex);
	if (!philo->info->end_simulation)
		printf("%llu %d is thinking\n",
			get_current_time_in_ms(), philo->number + 1);
	pthread_mutex_unlock(&philo->info->printf_mutex);
	if (philo->info->number_of_philos % 2 != 0)
	{
		think_time = (long long)philo->info->time_to_die
			- (long long)philo->info->time_to_eat
			- (long long)philo->info->time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time / 2);
	}
}

void	*kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (!philo->info->end_simulation)
		printf("%llu %d died\n",
			get_current_time_in_ms(), philo->number + 1);
	philo->info->end_simulation = 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (NULL);
}
