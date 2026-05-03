/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:20:39 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/03 00:31:36 by aalemami         ###   ########.fr       */
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
	initialized,
	has_one_fork,
	has_two_forks,
	eating,
	sleeping,
	thinking,
	dead
}	t_status;

typedef struct s_info
{
	int		number_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		maximum_eat_count;
}			t_info;

typedef struct s_philo
{
	int				number;
	pthread_mutex_t	fork;
	t_status		status;
	struct s_philo	*next;
	t_info			*info;
}					t_philo;

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

// execution

void				is_eating(t_philo *node);
void				is_sleeping(t_philo *node);
void				execution(t_philo *philo);

// connector
void	connector(char **argv);


#endif
