/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:43:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/03 19:42:11 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutexes(t_philo *node, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&node->fork);
		node = node->next;
		i++;
	}
}

static int	init_mutex_failure(t_philo **head, pthread_mutex_t *mutex, int i)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		ft_putstr_fd("mutex init failed.\n", 2);
		destroy_all_mutexes(*head, i);
		lstclear(head);
		return (1);
	}
	return (0);
}

int	initialize_all_mutexes(t_philo **head)
{
	t_philo	*philo;
	int		i;

	philo = *head;
	i = 0;
	while (philo->next != *head)
	{
		if (init_mutex_failure(head, &philo->fork, i) != 0)
			return (1);
		philo = philo->next;
		i++;
	}
	if (init_mutex_failure(head, &philo->fork, i) != 0)
			return (1);
	if (init_mutex_failure(head, &(*head)->info->printf_mutex, i + 1) != 0)
			return (1);
	return (0);
}

void	connector(char **argv)
{
	t_philo	*head;
	t_info	info;

	info = assign_argv_values(argv);
	head = circualr_linked_list(&info);
	if (!head)
		return ;
	if (initialize_all_mutexes(&head) != 0)
		return ;
	simulation(head);
	lstclear(&head);
}

