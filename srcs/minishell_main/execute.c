/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:28:27 by user42            #+#    #+#             */
/*   Updated: 2021/10/20 11:03:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void	ft_fork_n_go(int i, int *pid, t_exetrio *exe)
{
	if (!exe->cmd)
		return ;
	if (!exe->cmd[0])
		return ;
	if (ft_strcmp("cat", exe->cmd[0]) == 0 || ft_strcmp("wc", exe->cmd[0]) == 0)
		g_exit_code = 142;
	if (i == exe->no_cmds - 1)
	{
		exe->last_pid = fork();
		(*pid) = exe->last_pid;
	}
	else
		(*pid) = fork();
	if ((*pid) == 0)
		ft_inchild(i, exe);
	else
		ft_not_inchild(i, exe);
	if (exe->cmd)
		free_double(exe->cmd);
}

static int	ft_aftermath(t_exetrio *exe)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	waitpid(exe->last_pid, &status, 0);
	if (exe->last_exec_flag == 1 && exe->last_skip == 0 && g_exit_code != 131)
		g_exit_code = WEXITSTATUS(status);
	else if (g_exit_code == 131)
		g_exit_code = 130;
	while (waitpid(0, &status, 0) != -1)
		;
	i = -1;
	while (++i < exe->no_cmds - 1 && exe->pipefd[i])
	{
		if (exe->pipefd[i][0])
			close(exe->pipefd[i][0]);
		if (exe->pipefd[i][1])
			close(exe->pipefd[i][1]);
	}
	if (exe->cmd_str)
		free_double(exe->cmd_str);
	return (ft_ending(exe));
}

static void	ft_go_ahead(t_exetrio *exe, int i)
{
	int	pid;

	pid = 0;
	if (ft_str_empty(exe->cmd_str[i]) == 1)
		exe->cmd = &exe->cmd_str[i];
	else
	{
		exe->cmd = ft_split_quotes(exe->cmd_str[i], ' ');
		ft_echo_get_return(exe);
		if (ft_is_builtin_mod(&exe->cmd[0]) != 0)
			exe->cmd = ft_dequote(exe->cmd);
		else
			exe->cmd = ft_dequote_orig(exe->cmd);
		exe->exec_flag = 1;
		if (exe->cmd)
			ft_fork_n_go(i, &pid, exe);
		exe->prev_cmd = 0;
	}
	if (exe->tab_env)
		free_tab(exe->tab_env);
}

static int	ft_launch(t_exetrio *exe)
{
	int	i;

	i = -1;
	while (++i < exe->no_cmds)
	{
		if (i < (exe->no_cmds - 1) && pipe(exe->pipefd[i]) == -1)
			return (ft_piperr(exe, "Pipe() failed\n", 1));
		exe->cmd_str[i] = ft_input_sorter(exe->cmd_str[i], *exe);
		exe->skip = ft_directing_stuff(exe, i);
		if (i == exe->no_cmds - 1)
			exe->last_skip = exe->skip;
		if (exe->skip == 0)
		{
			exe->tab_env = ft_get_env_tab(exe);
			if (!exe->tab_env)
				ft_error("Malloc failed\n", 1);
			if (!exe->tab_env)
				return (ft_aftermath(exe));
			ft_go_ahead(exe, i);
		}
	}
	return (ft_aftermath(exe));
}

int	ft_execute_cl(char *cmd_line, t_exetrio *exe)
{
	if (ft_strcmp(cmd_line, "$") == 0)
	{
		printf("bash: $: command not found\n");
		g_exit_code = 127;
		free(cmd_line);
		exe->str = NULL;
		free(exe->input);
		free(exe->output);
		free(exe->direction);
		return (0);
	}
	exe->cmd_str = ft_split_quotes(cmd_line, '|');
	free(cmd_line);
	exe->str = NULL;
	exe->no_cmds = ft_get_no_cmds(exe->cmd_str);
	ft_make_pipefds(exe->no_cmds, exe);
	return (ft_launch(exe));
}
