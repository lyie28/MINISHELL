/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_commands_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 19:17:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../include/minishell.h"

static int	ft_cd_home(t_exetrio	*exe)
{
	char	*path2;
	char	*path3;
	int		test;

	test = 0;
	path2 = NULL;
	path3 = NULL;
	path3 = ft_strdup(" $HOME");
	path2 = ft_get_tab_variables(exe, &path3[1]);
	free(path3);
	if (!path2 || ft_strcmp("", path2) == 0)
	{
		free(path2);
		return (0);
	}
	test = chdir(path2);
	free(path2);
	if (test != 0)
	{
		perror("Error: ");
		return (1);
	}
	return (0);
}

int	ft_cd(char *path, t_exetrio *exe)
{
	int		test;
	int		i;

	test = 0;
	i = 1;
	while (exe->cmd[i])
		i++;
	if (i > 2)
	{
		printf("termicool: exit: too many arguments\n");
		return (1);
	}
	if (path == NULL)
		return (ft_cd_home(exe));
	if (ft_strcmp(path, "") == 0)
		return (0);
	test = chdir(path);
	if (test != 0)
	{
		perror("Error: ");
		return (1);
	}
	return (0);
}

static int	ft_exit_ending(char **str_status, t_exetrio *exe)
{
	int	i;

	i = 0;
	while (str_status[i])
		i++;
	if (i > 1)
	{
		printf("termicool: exit: too many arguments\n");
		return (1);
	}
	ft_exit_free(exe);
	exit(g_exit_code);
}

int	ft_exit(char **str_status, t_exetrio *exe)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if (exe->no_cmds == 1)
		write(1, "exit\n", 5);
	if (!str_status)
	{
		ft_exit_free(exe);
		exit (0);
	}
	if (str_status[0] && ft_atoi_mod(str_status[0], &status) == -1)
	{
		printf("termcool: exit: %s: numeric argument required\n", str_status[0]);
		ft_exit_free(exe);
		exit(2);
	}
	if (str_status[0])
		g_exit_code = status;
	return (ft_exit_ending(str_status, exe));
}
