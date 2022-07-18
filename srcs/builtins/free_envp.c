/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:25:26 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/18 13:14:20 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_envp(t_exetrio *exe)
{
	if (exe->e->head)
		ft_freelist_envp(exe->e->head);
	if (exe->e)
		free(exe->e);
}

void	ft_error_export(char *str)
{
	write(2, "bash: export: « ", 18);
	write(2, str, ft_strlen(str));
	write(2, " » : not a valid identifier", 29);
	write(2, "\n", 1);
}

void	ft_error_unset(char *str)
{
	write(2, "bash: unset: « ", 17);
	write(2, str, ft_strlen(str));
	write(2, " » : not a valid identifier", 29);
	write(2, "\n", 1);
}

int	ft_parse_errors_bis(char *str, int error)
{
	if (str[0] == '_' && str[1] == '=')
		g_exit_code = 1;
	if (str[0] == '_' && ft_isdigit(str[1]) == 1)
		g_exit_code = 0;
	if (str[0] == '=' || ft_isdigit(str[0]) || error == 1)
	{
		ft_error_export(str);
		g_exit_code = 1;
	}
	return (g_exit_code);
}

int	ft_init_export(char **str, t_exetrio *exe)
{
	exe->ret = -1;
	exe->j = 0;
	exe->any_bug = 0;
	g_exit_code = 0;
	if (!exe->e->head)
	{
		exe->ret = 1;
		return (exe->ret);
	}
	else if (str[exe->j] == NULL)
	{
		ft_lstprinter_export(exe->e);
		exe->ret = 0;
		return (exe->ret);
	}
	return (exe->ret);
}
