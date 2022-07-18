/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:03:36 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 19:39:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void	ft_free_paths(char **all_paths)
{
	int	i;

	i = -1;
	while (all_paths[++i])
		free(all_paths[i]);
	free((void *)all_paths);
}

char	*ft_getpath(char **all_paths, char *command)
{
	int			i;
	char		*base;
	char		*path;
	struct stat	buff;

	base = NULL;
	path = NULL;
	i = -1;
	while (all_paths[++i])
	{
		base = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(base, command);
		free(base);
		if (stat(path, &buff) == 0)
		{
			ft_free_paths(all_paths);
			return (path);
		}
		free(path);
	}
	ft_free_paths(all_paths);
	return (NULL);
}

char	*ft_pathfinder(char *command, char **tab_env)
{
	int		i;
	char	**all_paths;
	char	*copy;

	i = -1;
	all_paths = NULL;
	i = -1;
	while (tab_env[++i])
	{
		if (ft_strncmp(tab_env[i], "PATH", 4) == 0)
		{
			copy = ft_strdup(tab_env[i] + 5);
			all_paths = ft_split(copy, ':');
			free(copy);
			return (ft_getpath(all_paths, command));
		}
	}
	return (NULL);
}

void	ft_inchild(int i, t_exetrio *exe)
{
	int	temp;

	temp = 0;
	if (ft_is_builtin(exe->cmd) == 0 && exe->no_cmds > 1)
	{
		ft_connect_pipes(i, exe);
		g_exit_code = ft_cmd_control_room(exe->cmd, i, exe);
	}
	else if (ft_is_builtin(exe->cmd) == 1)
	{
		ft_connect_pipes(i, exe);
		if (ft_strcmp(exe->cmd[0], "cat") == 0)
			g_exit_code = 129;
		g_exit_code = ft_cmd(exe);
	}
	temp = g_exit_code;
	ft_exit_free (exe);
	exit (temp);
}

void	ft_not_inchild(int i, t_exetrio *exe)
{
	if (ft_is_builtin(exe->cmd) == 0 && exe->no_cmds == 1)
	{
		exe->exec_flag = 0;
		if (i == exe->no_cmds - 1)
			exe->last_exec_flag = 0;
		ft_connect_pipes(i, exe);
		g_exit_code = ft_cmd_control_room(exe->cmd, i, exe);
	}
	if (exe->no_cmds > 1)
		ft_parenting(i, exe->pipefd, exe->no_cmds);
}
