/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:22:43 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 03:44:42 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned long long ms)
{
	unsigned long long	start;

	start = get_current_time_in_ms();
	while (get_current_time_in_ms() - start < ms)
		usleep(500);
}

pthread_mutex_t	*get_fork_mutex(t_philo *philo)
{
	return (&philo->fork);
}
