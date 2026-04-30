/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:06:02 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/30 14:20:31 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// we wanna create a cirual linked list, each philosopher will have a status and his fork initialized




t_philo	*circualr_linked_list(char **argv, t_info *info)
{
	t_philo	*head;
	int		i;

	i = 0;
	while (i < info->number_of_philos)
	{
		head = malloc(sizeof(t_philo));
		head->info = info;
		head->status = initialized;
		head->number = i;
		pthread_mutex_init(&(head->fork), NULL);
	}
}