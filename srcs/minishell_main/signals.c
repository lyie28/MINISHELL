/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:17:16 by user42            #+#    #+#             */
/*   Updated: 2021/10/20 10:48:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	ft_sigint_two(void)
{
	if (g_exit_code == 129)
	{
		g_exit_code = 130;
		close(STDIN_FILENO);
		write(2, "\n", 1);
		return ;
	}
	if (g_exit_code != 142)
	{
		g_exit_code = 130;
		rl_replace_line("", 0);
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_sigint_ter(int pid, int signo)
{
	if (pid == 0 && signo == SIGINT && g_exit_code == 142)
	{
		write(2, "\n", 1);
		g_exit_code = 131;
	}
}

void	sigint_handler(int signo)
{
	int	status;
	int	pid;

	status = 0;
	pid = waitpid(-1, &status, WNOHANG);
	ft_sigint_ter(pid, signo);
	if (pid == -1 && signo == SIGINT)
	{
		ft_sigint_two();
		if (g_exit_code == 142)
		{
			close(STDIN_FILENO);
			write(2, "\n", 1);
			g_exit_code = 131;
		}
	}
	else if (pid == -1 && signo == 17 && (WIFSTOPPED(status)))
		exit (status);
}
