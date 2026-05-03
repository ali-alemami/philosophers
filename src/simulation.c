/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:46:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/03 20:16:28 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_for_all_philo_deaths(t_philo *philo)
{
	while (!philo)
	{
		if (philo->last_eat_time + philo->info->time_to_die > get_current_time_in_ms())
		{
			philo_died(philo);
		}
	}
}

void	set_last_eat_time(t_philo *head)
{
	t_philo	*philo;

	head->last_eat_time = head->info->start_of_simulation;
	philo = head->next;
	while (philo != head)
	{
		philo->last_eat_time = philo->info->start_of_simulation;
		philo = philo->next;
	}
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	taken_fork(philo, philo->fork);
	taken_fork(philo, philo->next->fork);
	is_eating(philo);
	is_sleeping(philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (NULL);
}

void	simulation(t_philo *head)
{
	t_philo	*philo;
	int	i;

	philo = head;
	philo->info->start_of_simulation = get_current_time_in_ms();
	set_last_eat_time(head);
	i = 0;
	while (i != philo->info->maximum_eat_count)
	{
		pthread_create(&philo->tid, NULL, philo_cycle, &philo);
		pthread_join(philo->tid, NULL);
		philo = philo->next;
		i++;
	}
}

	// philo1 take fork1 take fork2  starts eating philo2 sees fork busy w8 until phil1 finishes eating and goes to sleep then he takes the fork and starts eating
