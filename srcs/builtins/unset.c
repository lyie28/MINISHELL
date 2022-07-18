/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:43:21 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/18 12:12:19 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_loop_find_equal(char *str, int error)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			error = 1;
			break ;
		}
	}
	if (str[i] == '=')
		error = 1;
	return (error);
}

static int	ft_parse_errors_unset(char *str)
{
	int	ret;
	int	error;

	ret = 0;
	error = 0;
	if (str[0] == '\0')
	{
		ft_error_unset(str);
		ret = 1;
		return (ret);
	}
	error = ft_loop_find_equal(str, error);
	if (str[0] == '_' && str[1] == '=' && ft_isdigit(str[2]) == 1)
		return (-1);
	if (str[0] == '=' || ft_isdigit(str[0]) || error == 1)
	{
		ft_error_unset(str);
		ret = 1;
	}
	return (ret);
}

void	free_maillon(t_node *ptr1)
{
	if (ptr1->label)
		free(ptr1->label);
	if (ptr1->value)
		free(ptr1->value);
	if (ptr1)
		free(ptr1);
}

void	ft_remove_lst_env(t_list **alst, void *data)
{
	t_node		*current;
	t_node		*prev;

	current = (*alst)->head;
	while (current && ft_strcmp(current->label, data) == 0)
	{
		(*alst)->head = current->next;
		free_maillon(current);
		current = (*alst)->head;
	}
	while (current)
	{
		if (ft_strcmp(current->label, data) == 0)
		{
			prev->next = current->next;
			free_maillon(current);
			current = prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	ft_unset(t_exetrio *exe, char **str)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	if (str[j] == NULL)
		return (0);
	while (str[j])
	{
		if (ft_parse_errors_unset(str[j]) == 1
			|| ft_parse_errors_unset(str[j]) == -1)
		{
			ret = 1;
			if (str[j + 1])
				j++;
			else
				return (ret);
		}
		ft_remove_lst_env(&exe->e, str[j]);
		j++;
	}
	return (ret);
}
