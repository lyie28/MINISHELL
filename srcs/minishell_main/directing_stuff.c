/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directing_stuff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:28:27 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 11:53:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int	ft_frees_and_skip(t_exetrio *exe, t_dir_tools *tools)
{
	if (tools)
		free(tools);
	if (exe->dir_stuff_check == 0)
		dup2(exe->orig_stdout, 1);
	if (exe->input->head)
	{
		ft_freelist(exe->input->head);
		exe->input->head = NULL;
	}
	if (exe->output->head)
	{
		ft_freelist(exe->output->head);
		exe->output->head = NULL;
	}
	if (exe->direction->head)
	{
		ft_freelist_char(exe->direction->head);
		exe->direction->head = NULL;
	}
	if (g_exit_code == 130 && exe->dir_stuff_skip == 1)
		return (130);
	if (exe->dir_stuff_skip == 1)
		g_exit_code = exe->dir_stuff_skip;
	return (exe->dir_stuff_skip);
}

static int	ft_dir_in(t_exetrio *exe, int i, t_dir_tools *tools, t_node *input)
{
	int	error;

	error = 0;
	if (input)
	{
		error = (ft_init_first(input, exe));
		if (error != 0)
		{
			if (i < exe->no_cmds - 1)
				close(exe->pipefd[i][1]);
			exe->prev_cmd = 1;
			exe->dir_stuff_skip = 1;
			if (error == 1)
				g_exit_code = 1;
			if (g_exit_code == 130 && error == -2)
				return (130);
			return (1);
		}
		if (tools-> prev == NULL)
			tools->in = tools->in->next;
		return (0);
	}
	return (1);
}

static int	ft_dir_out(t_exetrio *exe, int i, t_dir_tools *tools, t_node *out)
{
	exe->dir_stuff_check = 1;
	if (out)
	{
		if (ft_init_last(out, tools->uni) != 0)
		{
			if (i > 0)
				close(exe->pipefd[i - 1][0]);
			if (i < exe->no_cmds - 1)
				close(exe->pipefd[i][1]);
			if (exe->dir_stuff_skip == 1)
				exe->prev_cmd = 3;
			else
				exe->prev_cmd = 2;
			g_exit_code = 1;
			exe->dir_stuff_skip = 1;
			return (1);
		}
		tools->out = tools->out->next;
		return (0);
	}
	return (1);
}

static void	ft_directing_init(t_exetrio *exe, t_dir_tools *tools)
{
	tools->prev = NULL;
	tools->temp = exe->direction->head;
	exe->dir_stuff_check = 0;
	exe->dir_stuff_skip = 0;
	if (exe->input->head)
		ft_dequote_list(exe->input->head);
	if (exe->output->head)
		ft_dequote_list(exe->output->head);
	tools->in = exe->input->head;
	tools->out = exe->output->head;
}

int	ft_directing_stuff(t_exetrio *exe, int i)
{
	t_dir_tools	*tools;

	tools = malloc(sizeof(t_dir_tools));
	if (!tools)
		return (ft_error("Malloc failed\n", 1));
	ft_directing_init(exe, tools);
	while ((tools->temp) && exe->dir_stuff_skip == 0)
	{
		tools->uni = 0;
		if (tools->temp->direction == '<' && tools->in->uni == 0)
			ft_dir_in(exe, i, tools, tools->in);
		else if (tools->temp->direction == '<' && tools->in->uni == 1)
			ft_diamond(tools);
		if (tools->temp->direction == '>')
			ft_dir_out(exe, i, tools, tools->out);
		if (tools->prev != NULL)
		{
			ft_dir_in(exe, i, tools, tools->prev);
			tools->in = tools->in->next;
			tools->prev = NULL;
		}
		tools->temp = tools->temp->next;
	}
	return (ft_frees_and_skip(exe, tools));
}
