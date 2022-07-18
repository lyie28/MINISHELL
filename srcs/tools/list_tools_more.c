/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:44:56 by lyie              #+#    #+#             */
/*   Updated: 2021/10/15 11:28:57 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

void	ft_lstadd_back(t_list *start, t_node *node)
{
	t_node	*current;

	if (start->head == NULL)
	{
		start->head = node;
		return ;
	}
	current = start->head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
	return ;
}

void	ft_lstadd_back_char(t_charlist *start, t_charnode *node)
{
	t_charnode	*current;

	if (start->head == NULL)
	{
		start->head = node;
		return ;
	}
	current = start->head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
	return ;
}

t_node	*ft_lstnew(char *file, int flag, int uni)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!(new))
		return (NULL);
	new->flag = flag;
	new->file = file;
	new->uni = uni;
	new->next = NULL;
	return (new);
}

void	ft_del_node(t_node *node)
{
	t_node	*temp;

	temp = node;
	if (node->next)
		node = node->next;
	else
		node = NULL;
}

t_charnode	*ft_lstnew_char(char c)
{
	t_charnode	*new;

	new = malloc(sizeof(t_charnode));
	if (!(new))
		return (NULL);
	new->direction = c;
	new->next = NULL;
	return (new);
}
