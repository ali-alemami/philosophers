/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:08:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/01 16:20:21 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


unsigned long long get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_philo	*lst;
	t_info	info;

	if (argc_validation(argc) || input_validation(argv) || validate_int_limits(argv))
		return (1);
	info = assign_argv_values(argv);
	lst = circualr_linked_list(&info);
	print_circular_list(lst);
	lstclear(&lst);
	return (0);
}

//n die eat sleep cycle_count