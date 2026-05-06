/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:20:39 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/06 18:58:05 by aalemami         ###   ########.fr       */
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

typedef enum s_philo_status
{
	INITIALIZED,
	HAS_ONE_FORK,
	HAS_TWO_FORKS,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DEAD
}	t_philo_status;

typedef struct s_info
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					maximum_eat_count;
	unsigned long long	start_of_simulation;
	pthread_mutex_t		printf_mutex;
	pthread_t			death_thread;
	int					end_simulation;
}						t_info;

typedef struct s_philo
{
	pthread_t			tid;
	int					number;
	pthread_mutex_t		fork;
	pthread_mutex_t		mutex;
	t_philo_status		status;
	int					eat_count;
	unsigned long long	last_eat_time;
	struct s_philo		*next;
	t_info				*info;
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
int					is_dead(t_philo *philo);
void				simulation(t_philo *head);

// philo cycle

void	take_first_fork(t_philo *philo);
void	take_second_fork(t_philo *philo);
void	is_eating(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
void	kill_philo(t_philo *philo);

// protected data

int	is_dead(t_philo *philo);
void	set_status(t_philo *philo, t_philo_status status);
void	set_last_eat_time_and_status(t_philo *philo);
void	print_message(t_philo *philo, char *str);
int	get_end_of_simulation_value(t_philo *philo);
unsigned long long	get_last_eat_time(t_philo *philo);


// create mutexex

pthread_mutex_t	*get_fork_mutex(t_philo *philo);
pthread_mutex_t	*get_status_mutex(t_philo *philo);

void	destroy_all_mutexex(t_philo *head,
	pthread_mutex_t *(*which_mutex)(t_philo *), int index);
int					init_all_mutexex(t_philo **head);

// connector

void				connector(char **argv);


#endif
