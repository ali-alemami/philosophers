/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:43:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/05 01:25:58 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	connector(char **argv)
{
	t_philo	*head;
	t_info	info;

	info = assign_argv_values(argv);
	head = circualr_linked_list(&info);
	if (!head)
		return ;
	if (init_all_mutexex(&head) != 0)
		return ;
	simulation(head);
	destroy_all_mutexex(head, get_fork_mutex, head->info->number_of_philos);
	destroy_all_mutexex(head, get_status_mutex, head->info->number_of_philos);
	lstclear(&head);
}

