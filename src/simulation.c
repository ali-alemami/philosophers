/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:46:36 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 15:54:30 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (get_end_of_simulation_value(philo) || is_philo_dead(philo))
			return (kill_philo(philo));
		i++;
		philo = philo->next;
		if (i == philo->info->number_of_philos)
		{
			if (flag == i)
				return (end_simulation(philo));
			ft_usleep(2);
			i = 0;
			flag = 0;
		}
	}
	return (NULL);
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
	if (philo->number % 2 != 0)
		ft_usleep(philo->info->time_to_eat);
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

static int	create_philo_threads(t_philo *head)
{
	t_philo	*philo;
	int		i;

	philo = head;
	i = 0;
	while (i < philo->info->number_of_philos)
	{
		if (pthread_create(&philo->tid, NULL, philo_cycle, philo) != 0)
		{
			ft_putstr_fd("Error: pthread_create failed\n", 2);
			end_simulation(philo);
			join_philo_threads(head, i);
			return (0);
		}
		philo = philo->next;
		i++;
	}
	return (1);
}

void	simulation(t_philo *head)
{
	t_philo	*philo;
	int		i;

	philo = head;
	set_first_last_eat_time(head);
	if (pthread_create(&head->info->death_thread, NULL,
			check_for_philos_deaths, head) != 0)
	{
		ft_putstr_fd("Error: death thread creation failed\n", 2);
		return ;
	}
	if (!create_philo_threads(head))
	{
		pthread_join(head->info->death_thread, NULL);
		return ;
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
