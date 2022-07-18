/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:52:57 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/18 16:45:06 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstprinter_env(t_list *lst)
{
	t_node	*current;

	if (!lst)
		return ;
	if (!lst->head)
		return ;
	current = lst->head;
	while (current)
	{
		if (!current->value)
			current = current->next;
		else
		{
			if (ft_strcmp(current->value, "\"\"") == 0)
				printf("%s=\n", current->label);
			else
				printf("%s=%s\n", current->label, current->value);
			current = current->next;
		}
	}
}

static int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_error_env(char *str)
{
	write(2, "env: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
}

static int	ft_print_env_strs(char **str, t_exetrio *exe)
{
	int	j;

	j = 0;
	ft_lstprinter_env(exe->e);
	while (str[j])
	{
		write(2, str[j], ft_strlen(str[j]));
		write(2, "\n", 1);
		j++;
	}
	return (0);
}

int	ft_env(t_exetrio *exe, char **str)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (!str[0])
	{
		ft_lstprinter_env(exe->e);
		return (0);
	}
	while (str[j])
	{
		if (check_equal(str[j]) == 1)
		{
			ft_error_env(str[j]);
			return (127);
		}
		j++;
		k++;
	}
	if (k == j)
		ft_print_env_strs(str, exe);
	return (0);
}
