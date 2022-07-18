/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 14:42:45 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 15:55:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../include/minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

static void	ft_get_input(t_exetrio *exe)
{
	char	*buf;

	buf = NULL;
	buf = readline("->->->:)");
	if (buf == NULL)
		ft_ctrld_free(exe);
	if ((ft_strlen(buf)) != 0)
	{
		add_history(buf);
		exe->str = ft_strdup(buf);
	}
	else
		exe->str = ft_strdup(buf);
}

/*if (!tmp) needs free before Malloc failed*/
static void	ft_get_env(char *env[], t_exetrio *exe)
{
	t_node	*tmp;
	int		i;

	init_exe_envp(exe);
	g_exit_code = 0;
	i = 0;
	tmp = NULL;
	exe->e = malloc(sizeof(t_list));
	if (!exe->e)
		exit (ft_error("Error: Malloc failed\n", 0));
	exe->e->head = NULL;
	while (env[i])
	{
		tmp = ft_newnode_envp(env[i], 1);
		if (!tmp)
		{
			if (exe->tab_env)
				free_tab(exe->tab_env);
			exit (ft_error("Error: Malloc failed\n", 0));
		}
		ft_lstadd_back(exe->e, tmp);
		i++;
	}
}

static void	ft_minishell_loop_ext(char *new, t_exetrio exe, char *str)
{
	if (ft_is_hang(str) == 1)
	{
		new = ft_hang_pipe(str, &exe);
		if (g_exit_code == 130)
		{
			ft_frees_in_main(exe, new);
			return ;
		}
		if (exe.hang != -1)
		{
			if (ft_punctuation(new, &exe) == 0 && ft_strlen(str) != 0)
			{
				free(str);
				ft_execute_cl(new, &exe);
			}
			else
				ft_frees_in_main(exe, new);
		}
		else
			ft_frees_in_main(exe, new);
	}
	else if (ft_punctuation(str, &exe) == 0 && ft_strlen(str) != 0)
		ft_execute_cl(str, &exe);
	else
		ft_frees_in_main(exe, new);
}

/* we will never reach code after while(1) */
int	minishell_loop(char *envp[])
{
	t_exetrio	exe;
	char		*new;

	new = NULL;
	ft_get_env(envp, &exe);
	ft_init_exe_p1(&exe);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	signal(SIGCHLD, sigint_handler);
	while (1)
	{
		ft_initialise_exe(&exe);
		dup2(exe.orig_stdin, STDIN_FILENO);
		dup2(exe.orig_stdout, STDOUT_FILENO);
		ft_get_input(&exe);
		if (ft_strlen(exe.str) > 0 && ft_punctuation(exe.str, &exe) == 0)
			ft_minishell_loop_ext(new, exe, exe.str);
		else
			ft_frees_in_main(exe, new);
		exe.hang = 0;
	}
	ft_exit_free(&exe);
	exit (0);
}

int	main(int argc, char **argv, char *envp[])
{
	(void)argv;
	(void)argc;
	write(1, "\n**WELCOME TO OUR SHELL***\n", 26);
	write(1, "\n\n\n\n\n\n\n\n********************\n", 29);
	minishell_loop(envp);
	return (0);
}
