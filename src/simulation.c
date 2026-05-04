/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:46:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/05 02:30:50 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_for_philos_deaths(void *arg)
{
	t_philo	*philo;
	int		flag;
	int		i;

	philo = (t_philo *)arg;
	flag = 1;
	while (flag == 1)
	{
		flag = 0;
		i = 0;
		while (i < philo->info->number_of_philos)
		{
			pthread_mutex_lock(&philo->mutex);
			if (philo->status != DEAD && philo->last_eat_time + philo->info->time_to_die <= get_current_time_in_ms())
				philo_died(philo);
			if (philo->status != DEAD)
				flag = 1;
			pthread_mutex_unlock(&philo->mutex);
			philo = philo->next;
			i++;
			ft_usleep(1);
		}
	}
	return NULL;
}

void	set_last_eat_time(t_philo *head)
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
	while (philo->status != DEAD && philo->eat_count != philo->info->maximum_eat_count)
	{
		take_first_fork(philo);
		take_second_fork(philo);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
		philo->eat_count++;
	}
	return (NULL);
}

void	simulation(t_philo *head)
{
	t_philo	*philo;
	int		i;

	philo = head;
	set_last_eat_time(head);
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
