/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 20:30:10 by lyie              #+#    #+#             */
/*   Updated: 2021/10/12 10:51:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

int	ft_freelist(t_node *head)
{
	t_node	*go;
	t_node	*temp;

	go = head;
	while (go != NULL)
	{
		free(go->file);
		temp = go;
		go = go->next;
		free(temp);
	}
	return (-1);
}

int	ft_freelist_char(t_charnode *head)
{
	t_charnode	*go;
	t_charnode	*temp;

	go = head;
	while (go != NULL)
	{
		temp = go;
		go = go->next;
		free(temp);
	}
	return (-1);
}

int	ft_freelist_envp(t_node *head)
{
	t_node	*go;
	t_node	*temp;

	go = head;
	while (go != NULL)
	{
		temp = go->next;
		free(go->label);
		if (go->value)
			free(go->value);
		free(go);
		go = temp;
	}
	return (-1);
}

void	ft_lstprinter(t_list *lst)
{
	t_node	*current;

	if (!lst)
		return ;
	if (!lst->head)
		return ;
	current = lst->head;
	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

int	ft_lstsize(t_node *head)
{
	t_node	*go;
	int		count;

	count = 0;
	go = head;
	if (go == NULL)
		return (0);
	count++;
	while (go->next)
	{
		count++;
		go = go->next;
	}
	return (count);
}
