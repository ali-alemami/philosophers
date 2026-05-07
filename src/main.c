/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:08:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/07 15:19:49 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_info	assign_argv_values(char **argv)
{
	t_info	info;

	info.number_of_philos = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info.maximum_eat_count = ft_atoi(argv[5]);
	else
		info.maximum_eat_count = -1;
	info.end_simulation = 0;
	return (info);
}

static void	connector(char **argv)
{
	t_philo	*head;
	t_info	info;

	info = assign_argv_values(argv);
	if (info.number_of_philos == 0)
		return (ft_putstr_fd("Error: number of philosophers must be > 0\n", 2));
	if (info.time_to_die == 0)
		return (ft_putstr_fd("Error: time_to_die must be > 0\n", 2));
	if (info.time_to_eat == 0)
		return (ft_putstr_fd("Error: time_to_eat must be > 0\n", 2));
	if (info.time_to_sleep == 0)
		return (ft_putstr_fd("Error: time_to_sleep must be > 0\n", 2));
	if (info.maximum_eat_count == 0)
		return (ft_putstr_fd("Error: must_eat must be > 0\n", 2));
	head = circualr_linked_list(&info);
	if (!head)
		return ;
	if (init_all_mutexex(&head) != 0)
		return ;
	simulation(head);
	destroy_all_mutexex(head);
	lstclear(&head);
}

int	main(int argc, char **argv)
{
	if (validate_all_args(argc, argv))
		return (1);
	connector(argv);
	return (0);
}
