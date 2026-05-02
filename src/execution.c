/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:38:42 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/02 21:53:18 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo *node)
{
	pthread_mutex_lock(&node->fork);
	printf("%llu %d is eating", get_current_time_in_ms(), node->number);
	ft_usleep(node->info->time_to_eat);
	pthread_mutex_unlock(&node->fork);
}

void	execution(t_philo *philo)
{
	// philo1 take fork1 take fork2  starts eating philo2 sees fork busy 
}