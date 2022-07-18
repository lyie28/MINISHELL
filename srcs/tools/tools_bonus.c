/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:43:27 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 11:46:13 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_error(char *error, int ret)
{
	write(2, error, ft_strlen(error));
	return (ret);
}

void	ft_cmd_error(char **cmd)
{
	int	i;

	i = 0;
	write(2, "command not found: ", 19);
	write(2, cmd[i], ft_strlen(cmd[i]));
	write(2, "\n", 1);
}

void	close_both(int pipefd[2])
{
	if (pipefd[0])
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
}

void	ft_make_pipefds(int no_cmds, t_exetrio *exe)
{
	int	i;

	i = 0;
	exe->pipefd = malloc((sizeof(int *)) * (no_cmds + 1));
	if (!exe->pipefd)
	{
		write(2, "Error: malloc failed\n", 21);
		exit (1);
	}
	while (i < no_cmds)
	{
		exe->pipefd[i] = malloc(sizeof(int) * 2);
		if (!exe->pipefd[i])
		{
			write(2, "Error: malloc failed\n", 21);
			ft_free_pipes(exe->pipefd);
			exit(1);
		}
		i++;
	}
	exe->pipefd[i] = 0;
}

void	ft_parenting(int counter, int **pipefd, int no_cmds)
{
	if (counter < no_cmds - 1)
		close(pipefd[counter][1]);
	if (counter != 0)
		close(pipefd[counter - 1][0]);
}
