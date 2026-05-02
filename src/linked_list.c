/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:06:02 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/02 13:24:33 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lstclear(t_philo **lst)
{
	t_philo	*head;
	t_philo	*tmp;

	if (!lst || !(*lst))
		return ;
	head = *lst;
	(*lst) = (*lst)->next;
	while (*lst != head)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	free(head);
	*lst = NULL;
}

static t_philo	*lstlast(t_philo *node)
{
	t_philo	*tmp;

	tmp = node;
	if (!node)
		return (NULL);
	while (node->next != tmp)
	{
		node = node->next;
	}
	return (node);
}

static void	lstadd_back(t_philo **head, t_philo *new)
{
	t_philo	*last;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last = lstlast(*head);
	last->next = new;
}

static t_philo	*make_node(t_philo **head, t_info *info, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		lstclear(head);
		perror("malloc");
		exit(1);
	}
	philo->number = i;
	philo->status = initialized;
	if (!(*head))
		(*head) = philo;
	philo->next = *head;
	philo->info = info;
	return (philo);
}

// void	print_circular_list(t_philo *head)
// {
// 	t_philo	*tmp;
// 	tmp = head;
// 	while (tmp->next != head)
// 	{
// 		printf("philo number [%d]\n", tmp->number);
// 		tmp = tmp->next;
// 	}
// 	printf("this is the last philo number [%d]\n", tmp->number);
// }

t_philo	*circualr_linked_list(t_info *info)
{
	t_philo	*head;
	int		i;

	head = NULL;
	i = 0;

	while (i < info->number_of_philos)
	{
		lstadd_back(&head, make_node(&head, info, i));
		i++;
	}
	return (head);
}
