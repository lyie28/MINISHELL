/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:42:47 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 11:24:14 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_herecmp(char *str)
{
	int		i;
	char	*check;

	i = 0;
	check = "here_doc";
	if (ft_strlen(str) != 8)
		return (1);
	while (i < 9 && str[i])
	{
		if (str[i] != check[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_exit_exe(int g_exit_code, int **pipes, t_exetrio exe)
{
	ft_free_exe(&exe, pipes);
	exit (g_exit_code);
}

int	ft_free_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	if (pipes)
		free (pipes);
	return (1);
}

void	failed_dup(int **pipes, t_exetrio *exe)
{
	ft_free_pipes(pipes);
	perror("Error: ");
	ft_exit_free(exe);
	exit (-1);
}

void	ft_free_exe(t_exetrio *exe, int **pipes)
{
	int	i;

	i = -1;
	if (exe->path)
		free((void *)exe->path);
	while (exe->command[++i])
		free((void *)exe->command[i]);
	if (exe->command)
		free((void *)exe->command);
	ft_free_pipes(pipes);
}
