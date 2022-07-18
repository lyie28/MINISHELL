/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:04:29 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/18 12:52:23 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parse_errors(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	g_exit_code = 0;
	if (!str)
		return (1);
	if (str[0] == '\0')
	{
		ft_error_export(str);
		g_exit_code = 1;
		return (g_exit_code);
	}
	while (str[i] && str[i] != '=')
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '\"')
			|| (str[i] == '\"' && str[i + 1] == '\"'))
			error = 1;
		i++;
	}
	g_exit_code = ft_parse_errors_bis(str, error);
	return (g_exit_code);
}

t_node	*ft_newnode_envp(char *file, int i)
{
	t_node	*new;
	int		pos;

	new = malloc(sizeof(t_node));
	if (!(new))
		return (NULL);
	new->label = NULL;
	new->value = NULL;
	if (i == 1)
	{
		pos = ft_strchr(file, '=');
		new->label = ft_substr(file, 0, pos);
		new->value = parsing_quotes(file, pos);
	}
	else if (i == 0)
		new->label = ft_strdup(file);
	new->next = NULL;
	file = NULL;
	return (new);
}

t_node	*ft_lstnew_forcpy(char *label, char *value)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!(new))
		return (NULL);
	new->value = NULL;
	if (value)
		new->value = ft_strdup(value);
	if (label)
		new->label = ft_strdup(label);
	new->next = NULL;
	return (new);
}

static int	ft_check_lst(t_list *lst)
{
	if (!lst)
		return (1);
	if (!lst->head)
		return (1);
	return (0);
}

void	ft_lstprinter_export(t_list *lst)
{
	t_node	*current;
	int		i;

	i = 0;
	if (ft_check_lst(lst) == 1)
		return ;
	current = lst->head;
	while (current)
	{
		if (!(current->value))
		{	
			ft_sortlst_alpha(lst);
			printf("declare -x %s\n", current->label);
		}
		else if (current->value)
		{
			ft_sortlst_alpha(lst);
			if (current->value[0] == '\"')
				printf("declare -x %s=%s\n", current->label, current->value);
			else
				printf("declare -x %s=\"%s\"\n", current->label, current->value);
		}
		current = current->next;
	}
}
