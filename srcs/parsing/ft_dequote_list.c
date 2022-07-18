/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequote_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 12:39:01 by user42            #+#    #+#             */
/*   Updated: 2021/10/03 19:25:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/minishell.h"

static int	ft_not_only(char *str)
{
	int		i;
	char	*check;

	if (str[0] == '\"')
		check = "\"";
	else
		check = "\'";
	i = 0;
	while (str[i])
	{
		if (ft_is_this((char *)check, str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static void	ft_create_new(t_node *current, char ting)
{
	int		size;
	int		x;
	int		q;
	char	*new;

	x = 0;
	q = 0;
	while (current->file[q] == ting)
		q++;
	size = (ft_strlen(current->file) - (2 * q));
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return ;
	while (x < size && current->file[x + q])
	{
		new[x] = current->file[x + q];
		x++;
	}
	new[x] = '\0';
	free(current->file);
	current->file = new;
}

void	ft_dequote_list(t_node *head)
{
	int		i;
	t_node	*current;

	i = 0;
	current = head;
	while (current)
	{
		if (current->file)
		{
			if (current->file[0] == '\"' || current->file[0] == '\'')
			{
				if (ft_not_only(current->file) == 0)
					ft_create_new(current, current->file[0]);
				else
				{
					free(current->file);
					current->file = ft_strdup("");
				}
			}
		}
		current = current->next;
	}
}
