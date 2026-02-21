/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:22:28 by aalemami          #+#    #+#             */
/*   Updated: 2026/02/16 22:22:28 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_data	t_data;

typedef struct	s_philo
{
	int				philo_id;
	pthread_t		philo_thread;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

struct	s_data
{
	int				number_of_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_eat_count;
	pthread_mutex_t write_mutex;
	t_philo			*list_of_philos;
	pthread_mutex_t	*list_of_forks;
};

int	ft_atoi(const char *nptr);
