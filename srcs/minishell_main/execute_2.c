/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:07:23 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 14:04:15 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int	ft_search_command(char **split, t_exetrio *exec)
{
	struct stat	buff;
	char		*path;

	path = NULL;
	if (stat(split[0], &buff) == 0)
	{
		if (S_ISREG(buff.st_mode) && ft_got_slash(split[0]) == 0)
		{
			exec->path = ft_strdup((char *)split[0]);
			exec->command = (char *const *)split;
			return (0);
		}
	}
	path = ft_pathfinder(split[0], exec->tab_env);
	if (path == NULL)
	{
		ft_cmd_error(split);
		return (-1);
	}
	exec->path = (const char *)path;
	exec->command = (char *const *)split;
	return (0);
}

/* dequote split after split_quotes?*/
int	init_exetrio(char **command, t_exetrio *exec)
{
	char		**split;
	char		*path;
	struct stat	buff;

	split = command;
	path = NULL;
	if (stat(split[0], &buff) == 0 && buff.st_mode & S_IXUSR)
	{
		if (S_ISDIR(buff.st_mode))
		{
			printf("termicool: %s is a directory\n", split[0]);
			return (-1);
		}
		else if (S_ISREG(buff.st_mode) && ft_got_slash(split[0]) != 0)
		{
			ft_cmd_error(split);
			return (-1);
		}
		else
			path = ft_strdup((char *)split[0]);
		exec->path = (const char *)path;
		exec->command = (char *const *)split;
		return (0);
	}
	return (ft_search_command(split, exec));
}

void	ft_initialise_exe(t_exetrio *exe)
{
	exe->input = malloc(sizeof(t_list));
	if (!exe->input)
		return ;
	exe->output = malloc(sizeof(t_list));
	if (!exe->output)
		return ;
	exe->direction = malloc(sizeof(t_charlist));
	if (!exe->direction)
		return ;
	exe->input->head = NULL;
	exe->output->head = NULL;
	exe->direction->head = NULL;
	exe->path = NULL;
	exe->command = NULL;
	exe->skip = 0;
}

int	ft_get_no_cmds(char **pipe_strings)
{
	int	counter;

	counter = 0;
	while (pipe_strings[counter])
		counter++;
	return (counter);
}
