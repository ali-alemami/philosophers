/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 22:31:20 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/02 23:11:36 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo *node)
{
	printf("%llu %d is eating\n", get_current_time_in_ms(), node->number);
	ft_usleep(node->info->time_to_eat);
}

void	is_sleeping(t_philo *node)
{
	printf("%llu %d is sleeping\n", get_current_time_in_ms(), node->number);
	ft_usleep(node->info->time_to_sleep);
}
