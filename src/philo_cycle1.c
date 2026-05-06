/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:47:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 04:02:21 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (is_dead(philo) || get_end_of_simulation_value(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	if (!is_dead(philo) && get_end_of_simulation_value(philo) != 1)
		print_message(philo, "has taken a fork");
	set_status(philo, HAS_ONE_FORK);
}

void	take_second_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	if (is_dead(philo) || get_end_of_simulation_value(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return ;
	}
	if (!is_dead(philo) && get_end_of_simulation_value(philo) != 1)
		print_message(philo, "has taken a fork");
	set_status(philo, HAS_TWO_FORKS);
}
