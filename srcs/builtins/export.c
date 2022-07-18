/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:21 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/19 11:16:04 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_label_exist(t_exetrio *exe, char *str)
{
	int		pos;
	char	*label_to_search;
	char	*value_to_add;
	t_node	*current;

	current = exe->e->head;
	pos = ft_strchr(str, '=');
	label_to_search = ft_substr(str, 0, pos);
	value_to_add = parsing_quotes(str, pos);
	while (current)
	{
		if (ft_strcmp(label_to_search, current->label) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value_to_add);
			free(label_to_search);
			free(value_to_add);
			return (1);
		}
		current = current->next;
	}
	free(label_to_search);
	free(value_to_add);
	return (0);
}

static int	check_label(t_exetrio *exe, char *str)
{
	t_node	*current;

	current = exe->e->head;
	while (current)
	{
		if (ft_strcmp(str, current->label) == 0)
		{
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static void	ft_export_loop(t_exetrio *exe, char *str)
{
	int		i;
	t_node	*elem;

	elem = NULL;
	exe->label_added = 0;
	exe->assign_var = 0;
	i = -1;
	if (!str)
		return ;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			exe->label_added = check_label_exist(exe, str);
			exe->assign_var = 1;
		}
	}
	if (check_label(exe, str) == 1 && exe->assign_var == 0)
		return ;
	else if (exe->assign_var == 1 && exe->label_added == 0)
		elem = ft_newnode_envp(str, 1);
	else if (exe->assign_var == 0)
		elem = ft_newnode_envp(str, 0);
	ft_lstadd_back(exe->e, elem);
}

/*static int	handle_str_null(t_exetrio *exe)
{
	t_list	*to_sort;

	to_sort = NULL;
	to_sort = ft_duplicate_list(to_sort, exe->e);
	ft_lstprinter_export(to_sort);
	ft_freelist_envp(to_sort->head);
	free(to_sort);
	return (g_exit_code);
}*/

int	ft_export(t_exetrio *exe, char **str)
{
	if (ft_init_export(str, exe) >= 0)
		return (exe->ret);
	while (str[exe->j])
	{
		if (ft_strcmp(str[exe->j], "$?") == 0
			|| ft_strcmp(str[exe->j], "'$?'") == 0)
			exe->j++;
		g_exit_code = ft_parse_errors(str[exe->j]);
		if (g_exit_code == 0)
		{
			ft_export_loop(exe, str[exe->j]);
			exe->j++;
		}
		else if (g_exit_code == 1)
		{
			exe->j++;
			if (!str[exe->j])
				return (1);
		}
		if (g_exit_code == 1)
			exe->any_bug = 1;
	}
	if (exe->any_bug == 1)
		g_exit_code = 1;
	return (g_exit_code);
}
