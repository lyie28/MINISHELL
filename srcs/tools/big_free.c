/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:43:32 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 15:56:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

void	ft_ctrld_free(t_exetrio *exe)
{
	if (exe->input)
		free(exe->input);
	if (exe->output)
		free (exe->output);
	if (exe->direction)
		free (exe->direction);
	ft_free_envp(exe);
	rl_clear_history();
	exit (0);
}

void	ft_exit_free(t_exetrio *exe)
{
	if (exe->output)
		free(exe->output);
	if (exe->input)
		free(exe->input);
	if (exe->direction)
		free(exe->direction);
	if (exe->cmd_str)
		free_double(exe->cmd_str);
	if (exe->cmd)
		free_double(exe->cmd);
	if (exe->pipefd)
		ft_free_pipes(exe->pipefd);
	if (exe->tab_env)
		free_tab(exe->tab_env);
	ft_free_envp(exe);
	rl_clear_history();
}

int	ft_ret_free(int ret, t_exetrio *exe)
{
	if (exe->output)
	{
		if (exe->output->head)
			ft_freelist(exe->output->head);
	}
	if (exe->cmd_str)
		free_double(exe->cmd_str);
	if (exe->cmd)
		free_double(exe->cmd);
	if (exe->pipefd)
		ft_free_pipes(exe->pipefd);
	if (exe->tab_env)
		free_tab(exe->tab_env);
	return (ret);
}
