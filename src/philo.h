/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:20:39 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/01 16:20:10 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"

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
int		argc_validation(int argc);
int		input_validation(char **argv);
int		validate_int_limits(char **argv);

// tokenization
t_info	assign_argv_values(char **argv);

// linked list
void	print_circular_list(t_philo *head);
t_philo	*circualr_linked_list(t_info *info);
void	lstclear(t_philo **lst);


#endif
