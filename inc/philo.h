/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:20:39 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/03 19:52:26 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

typedef enum s_status
{
	INITIALIZED,
	HAS_ONE_FORK,
	HAS_TWO_FORKS,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DEAD
}	t_status;

typedef struct s_info
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					maximum_eat_count;
	unsigned long long	start_of_simulation;
	pthread_mutex_t		printf_mutex;
}						t_info;

typedef struct s_philo
{
	pthread_t			tid;
	int					number;
	unsigned long long	last_eat_time;
	t_status			status;
	pthread_mutex_t		fork;
	t_info				*info;
	struct s_philo		*next;
}						t_philo;

// validation

int					validate_all_args(char argc, char **argv);

// tokenization

t_info				assign_argv_values(char **argv);

// linked list

void				lstclear(t_philo **lst);
t_philo				*circualr_linked_list(t_info *info);

// utils

unsigned long long 	get_current_time_in_ms(void);
void				ft_usleep(unsigned long long ms);
void				ft_putstr_fd(char *s, int fd);
int					ft_str_isdigit(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *nptr);

// simulation

void				taken_fork(t_philo *philo, pthread_mutex_t fork);
void				is_eating(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				philo_died(t_philo *philo);
void				simulation(t_philo *philo);

// connector
void	connector(char **argv);


#endif
