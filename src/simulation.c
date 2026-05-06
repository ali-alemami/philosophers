/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:46:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 19:44:10 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_for_philos_deaths(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_current_time_in_ms() >= get_last_eat_time(philo) + philo->info->time_to_die)
		{
			kill_philo(philo);
			return (NULL);
		}
		philo = philo->next;
	}
	return NULL;
}

void	set_first_last_eat_time(t_philo *head)
{
	t_philo	*philo;

	head->info->start_of_simulation = get_current_time_in_ms();
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
	while (get_end_of_simulation_value(philo) != 1)
	{
		take_first_fork(philo);
		take_second_fork(philo);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

void	simulation(t_philo *head)
{
	t_philo	*philo;
	int		i;

	philo = head;
	set_first_last_eat_time(head);
	pthread_create(&head->info->death_thread, NULL, check_for_philos_deaths, head);
	i = 0;
	while (i < philo->info->number_of_philos)
	{
		pthread_create(&philo->tid, NULL, philo_cycle, philo);
		philo = philo->next;
		i++;
	}
	philo = head;
	i = 0;
	while (i < philo->info->number_of_philos)
	{
		pthread_join(philo->tid, NULL);
    	philo = philo->next;
    	i++;
	}
	pthread_join(head->info->death_thread, NULL);
}
