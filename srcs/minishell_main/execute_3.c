/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:22:22 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 18:22:36 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*close [count -1][1] in first line of first bracket?*/
void	ft_connect_pipes(int count, t_exetrio *exe)
{
	if (count != 0)
	{
		if (dup2(exe->pipefd[count - 1][0], 0) == -1)
			failed_dup(exe->pipefd, exe);
		close(exe->pipefd[count - 1][0]);
	}
	if (count < (exe->no_cmds) - 1)
	{
		close(exe->pipefd[count][0]);
		if (dup2(exe->pipefd[count][1], 1) == -1)
			failed_dup(exe->pipefd, exe);
		close(exe->pipefd[count][1]);
	}
}

/*TODO check if free is correct*/
int	ft_cmd(t_exetrio *exe)
{
	if (init_exetrio(exe->cmd, exe) == 0)
	{
		if (execve(exe->path, exe->command, exe->tab_env) != 0)
		{
			perror("Error: ");
			free((char *)exe->path);
			if (errno == 13)
				return (126);
			free_double((char **)exe->command);
			return (127);
		}
		else
		{
			g_exit_code = 0;
			free((char *)exe->path);
			free_double((char **)exe->command);
			return (0);
		}
	}
	if (exe->path)
		free((char *)exe->path);
	if (exe->command)
		free_double((char **)exe->command);
	return (127);
}

int	ft_is_builtin(char **cmd_line)
{
	if (ft_strcmp(cmd_line[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "export") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "env") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "unset") == 0)
		return (0);
	else
		return (1);
}

int	ft_is_builtin_mod(char **cmd_line)
{
	if (ft_strcmp(cmd_line[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "export") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "env") == 0)
		return (0);
	else if (ft_strcmp(cmd_line[0], "unset") == 0)
		return (0);
	else
		return (1);
}
