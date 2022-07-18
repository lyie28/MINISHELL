/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:54:07 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/09/27 16:35:23 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_duplicate_list(t_list *to_sort, t_list *begin_list)
{
	t_node	*tmp;
	t_node	*tracker;

	tmp = NULL;
	tracker = begin_list->head;
	to_sort = malloc(sizeof(t_list));
	if (!to_sort)
		return (NULL);
	to_sort->head = NULL;
	if (!begin_list->head)
		return (NULL);
	while (tracker)
	{
		tmp = ft_lstnew_forcpy(tracker->label, tracker->value);
		ft_lstadd_back(to_sort, tmp);
		tracker = tracker->next;
	}
	return (to_sort);
}

int	check_label_added(t_exetrio *exe, char *str)
{
	t_node	*current;

	current = NULL;
	if (!str)
		return (0);
	current = exe->e->head;
	while (current)
	{
		if (ft_strcmp(str, current->label) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	init_exe_envp(t_exetrio *exe)
{
	exe->e = NULL;
	exe->tab_env = NULL;
}

int	ft_check_quotes(char *str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 1;
	if (str[0] == '\"')
		quote = 1;
	while (str[i])
	{
		if (str[i] == '\"')
			quote++;
		i++;
	}
	if (quote > 0)
		return (1);
	return (0);
}

char	*handle_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(str));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		new[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (new);
}
