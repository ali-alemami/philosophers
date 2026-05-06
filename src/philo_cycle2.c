/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 01:03:33 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 04:06:41 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo *philo)
{
	if (!is_dead(philo) && get_end_of_simulation_value(philo) != 1)
		print_message(philo, "is eating");
	set_last_eat_time_and_status(philo);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	is_sleeping(t_philo *philo)
{
	if (!is_dead(philo) && get_end_of_simulation_value(philo) != 1)
		print_message(philo, "is sleeping");
	set_status(philo, IS_SLEEPING);
	ft_usleep(philo->info->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	if (!is_dead(philo) && get_end_of_simulation_value(philo) != 1)
		print_message(philo, "is thinking");
	set_status(philo, IS_THINKING);
}

void	kill_philo(t_philo *philo)
{
	print_message(philo, "died");
	philo->status = DEAD;
	pthread_mutex_lock(&philo->info->printf_mutex);
	philo->info->end_simulation = 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
}
