/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:05:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 04:06:10 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->mutex);
	res = philo->status == DEAD;
	pthread_mutex_unlock(&philo->mutex);
	return (res);
}

void	set_status(t_philo *philo, t_philo_status status)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->status != DEAD)
		philo->status = status;
	pthread_mutex_unlock(&philo->mutex);
}

void	set_last_eat_time_and_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->status != DEAD)
	{
		philo->last_eat_time = get_current_time_in_ms();
		philo->status = IS_EATING;
		philo->eat_count++;
	}
	pthread_mutex_unlock(&philo->mutex);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%llu %d %s\n", get_current_time_in_ms(), philo->number, str);
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

int	get_end_of_simulation_value(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->info->printf_mutex);
	res = philo->info->end_simulation == 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (res);
}