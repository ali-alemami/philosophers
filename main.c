/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:35:06 by aalemami          #+#    #+#             */
/*   Updated: 2026/02/14 13:35:06 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
#include <sys/time.h>

void	assign_args(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat_count = ft_atoi(argv[5]);	
}

int	create_philos_forks(t_data *data)
{
	data->list_of_philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->list_of_philos)
		return (1);
	data->list_of_forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->list_of_forks)
	{
		free(data->list_of_philos);
		data->list_of_philos = NULL;
		return (1);
	}
	return (0);
}

void	assign_philos_args(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->list_of_philos[i].philo_id = i;
		data->list_of_philos[i].last_meal_time = 0;
		data->list_of_philos[i].meals_eaten = 0;
		data->list_of_philos[i].left_fork = &data->list_of_forks[i];
		data->list_of_philos[i].right_fork = &data->list_of_forks[(i + 1) % data->number_of_philos];
		data->list_of_philos[i].data = data;
		i++;
	}
}

int	init_all_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->list_of_forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->list_of_forks);
			}
			write(2, "Error: Mutex initialization failed\n", 35);
			return (1);
		}
		i++;
	}
	return (0);
}

void	take_two_forks(t_philo *philo)
{
	struct timeval	tv;
	long long 		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_lock(&philo->left_fork);
	printf("%lld %d has taken a fork\n", current_time, philo->philo_id);
	pthread_mutex_lock(&philo->right_fork);
	printf("%lld %d has taken a fork\n", current_time, philo->philo_id);
}

void	take_all_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		take_two_forks(&data->list_of_philos[i]);
		i++;
	}
}

void	one_philosopher_eating(t_philo *philo)
{
	struct timeval	tv;
	long long 		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%lld %d is eating\n", current_time, philo->philo_id);
	usleep(philo->data->time_to_eat * 1000);
}

void	all_philosophers_eating(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		one_philosopher_eating(&data->list_of_philos[i]);
		i++;
	}
}

int	start_process(t_data *data)
{
	create_philos_forks(data);
	assign_philos_args(data);
	if (init_all_forks(data) != 0)
		return (1);
	take_all_forks(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: Wrong number of parameters.\n");
		return (1);
	}
	assign_args(&data, argc, argv);
}