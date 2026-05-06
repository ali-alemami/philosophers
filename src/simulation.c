/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:46:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 00:37:21 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_eat_count(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->info->printf_mutex);
	res = philo->eat_count >= philo->info->maximum_eat_count;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (res);
}

static void	*end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	philo->info->end_simulation = 1;
	pthread_mutex_unlock(&philo->info->printf_mutex);
	return (NULL);
}

static void	*check_for_philos_deaths(void *arg)
{
	t_philo	*philo;
	int		flag;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	flag = 0;
	while (i < philo->info->number_of_philos)
	{
		if (philo->info->maximum_eat_count != -1 && philo_eat_count(philo))
			flag++;
		if (get_current_time_in_ms() >= get_last_eat_time(philo) + philo->info->time_to_die)
			return (kill_philo(philo));
		i++;
		philo = philo->next;
		if (i == philo->info->number_of_philos)
		{
			if (flag == i)
				return (end_simulation(philo));
			ft_usleep(5);
			i = 0;
			flag = 0;
		}
	}
	return NULL;
}

static void	set_first_last_eat_time(t_philo *head)
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

static void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->number_of_philos == 1)
	{
		take_first_fork(philo);
		ft_usleep(philo->info->time_to_die + 10);
		pthread_mutex_unlock(&philo->fork);
		return (NULL);
	}
	while (get_end_of_simulation_value(philo) != 1)
	{
		if (!take_first_fork(philo))
			break ;
		if (!take_second_fork(philo))
			break ;
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
