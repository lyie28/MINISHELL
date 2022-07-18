/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:46:41 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 14:47:44 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_exe_p1(t_exetrio *exe)
{
	exe->str = NULL;
	exe->exec_flag = 1;
	exe->last_exec_flag = 1;
	exe->last_pid = 0;
	exe->last_skip = 0;
	exe->orig_stdin = dup(STDIN_FILENO);
	exe->orig_stdout = dup(STDOUT_FILENO);
	exe->no_cmds = 0;
	exe->hang = 0;
	exe->pipefd = NULL;
	exe->cmd = NULL;
	exe->cmd_str = NULL;
}
