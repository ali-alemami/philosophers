/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutexex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:51:39 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 01:04:00 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_all_mutexex(t_philo *head,
	pthread_mutex_t *(*which_mutex)(t_philo *), int index)
{
	t_philo	*philo;
	int		i;

	philo = head;
	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(which_mutex(philo));
		philo = philo->next;
		i++;
	}
}

static int	init_fork_mutexex(t_philo **head)
{
	t_philo	*philo;
	int		i;

	philo = *head;
	i = 0;
	while (philo->next != (*head))
	{
		if (pthread_mutex_init(&philo->fork, NULL) != 0)
		{
			destroy_all_mutexex(*head, get_fork_mutex, i);
			return (1);
		}
		philo = philo->next;
		i++;
	}
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
	{
		destroy_all_mutexex(*head, get_fork_mutex, i);
		return (1);
	}
	return (0);
}

static int	init_status_mutexex(t_philo **head)
{
	t_philo	*philo;
	int		i;

	philo = *head;
	i = 0;
	while (philo->next != (*head))
	{
		if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		{
			destroy_all_mutexex(*head,
				get_fork_mutex, philo->info->number_of_philos);
			destroy_all_mutexex(*head, get_status_mutex, i);
			return (1);
		}
		philo = philo->next;
		i++;
	}
	if (pthread_mutex_init(&philo->mutex, NULL) != 0)
	{
		destroy_all_mutexex(*head,
			get_fork_mutex, philo->info->number_of_philos);
		destroy_all_mutexex(*head, get_status_mutex, i);
		return (1);
	}
	return (0);
}

int	init_all_mutexex(t_philo **head)
{
	if (init_fork_mutexex(head) == 1 || init_status_mutexex(head) == 1)
	{
		lstclear(head);
		return (1);
	}
	if (pthread_mutex_init(&(*head)->info->printf_mutex, NULL) != 0)
	{
		destroy_all_mutexex(*head,
			get_fork_mutex, (*head)->info->number_of_philos);
		destroy_all_mutexex(*head,
			get_status_mutex, (*head)->info->number_of_philos);
		lstclear(head);
		return (1);
	}
	return (0);
}
