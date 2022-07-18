/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_comands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 11:15:33 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../include/minishell.h"

/*TODO: export, unset, env*/
int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, 1024) == NULL)
	{
		perror("Error: ");
		return (1);
	}
	write(1, "Dir: ", 6);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

int	ft_echo(char **str)
{
	int	i;
	int	offset;

	i = -1;
	if (ft_strcmp(str[1], "-n") == 0)
		offset = 2;
	else
		offset = 1;
	while (str[offset + (++i)])
	{
		if (i > 0)
			write(1, " ", 1);
		if (str[offset + i][0])
		{
			if (!(write(1, str[offset + i], ft_strlen(str[offset + i]))))
			{
				perror("Error: ");
				return (-1);
			}
		}
	}
	if (offset == 1)
		write(1, "\n", 1);
	return (0);
}

int	ft_cmd_control_room(char **cmd_line, int index, t_exetrio *exe)
{
	int	exit_code;

	(void)index;
	exit_code = 0;
	if (ft_strcmp(cmd_line[0], "pwd") == 0)
		exit_code = ft_pwd();
	else if (ft_strcmp(cmd_line[0], "cd") == 0)
		exit_code = ft_cd(cmd_line[1], exe);
	else if (ft_strcmp(cmd_line[0], "exit") == 0)
		exit_code = ft_exit(&cmd_line[1], exe);
	else if (ft_strcmp(cmd_line[0], "echo") == 0)
		exit_code = ft_echo(exe->cmd);
	else if (ft_strcmp(cmd_line[0], "export") == 0)
		exit_code = ft_export(exe, &cmd_line[1]);
	else if (ft_strcmp(cmd_line[0], "env") == 0)
		exit_code = ft_env(exe, &cmd_line[1]);
	else if (ft_strcmp(cmd_line[0], "unset") == 0)
		exit_code = ft_unset(exe, &cmd_line[1]);
	return (exit_code);
}
