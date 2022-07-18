/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_in_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:49:28 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/12 17:56:03 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_create_strenv(char *str, char *label, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (label[i])
	{
		str[i] = label[i];
		i++;
	}
	if (!value)
		return ;
	str[i++] = '=';
	j = 0;
	while (value[j])
	{
		str[i++] = value[j++];
	}
	str[i] = '\0';
}

static int	get_size_lst(t_node *current)
{
	int	i;

	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

static char	**ft_free_new_env(char **new)
{
	free_double(new);
	return (NULL);
}

char	**ft_get_env_tab(t_exetrio *exe)
{
	int		i;
	char	**new;
	t_node	*current;

	current = exe->e->head;
	i = 0;
	exe->len_tab = get_size_lst(current);
	new = malloc(sizeof(char *) * (exe->len_tab + 1));
	if (!new)
		return (NULL);
	current = exe->e->head;
	while (current)
	{
		new[i] = malloc(sizeof(char) * (ft_strlen(current->label)
					+ ft_strlen(current->value) + 2));
		if (!new[i])
			return (ft_free_new_env(new));
		ft_create_strenv(new[i], current->label, current->value);
		i++;
		current = current->next;
	}
	new[exe->len_tab] = 0;
	return (new);
}
