/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:43:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/02 18:22:38 by aalemami         ###   ########.fr       */
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

int	initialize_all_mutexes(t_philo **head)
{
	t_philo	*node;
	int		i;

	node = *head;
	i = 0;
	while (node->next != *head)
	{
		if (pthread_mutex_init(&node->fork, NULL) != 0)
		{
			ft_putstr_fd("mutex init failed.\n", 2);
			destroy_all_mutexes(*head, i);
			lstclear(head);
			return (1);
		}
		node = node->next;
		i++;
	}
	if (pthread_mutex_init(&node->fork, NULL) != 0)
	{
		ft_putstr_fd("mutex init failed.\n", 2);
		destroy_all_mutexes(*head, i);
		lstclear(head);
		return (1);
	}
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
}

