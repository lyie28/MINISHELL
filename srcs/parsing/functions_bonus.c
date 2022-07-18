/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:03:36 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 12:12:59 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_last_heredoc(t_node *tmp)
{
	while (tmp)
	{
		if (tmp->flag == 1)
			return (0);
		else
			tmp = tmp->next;
	}
	return (1);
}

static int	ft_go_setter(int *go, t_node *current, int *fd, t_exetrio *exe)
{
	int	error;

	error = 0;
	*go = 0;
	if (current->flag == 0)
		*go = 1;
	else if (ft_last_heredoc(current->next) == 1)
		*go = 2;
	if (*go == 1)
		*fd = open(current->file, O_RDONLY);
	if (*go == 2)
	{
		error = here_doc(current->file, ".here_doc", exe->pipefd);
		if (error != 0)
			return (error);
		*fd = open(".here_doc", O_RDONLY);
	}
	return (0);
}

int	ft_init_first(t_node *input, t_exetrio *exe)
{
	int		fd;
	t_node	*current;
	int		go;
	int		error;

	go = 0;
	current = input;
	error = (ft_go_setter(&go, current, &fd, exe));
	if (error < 0)
		return (error);
	if (go > 0)
	{
		if (fd < 0)
			perror(current->file);
		if (fd < 0)
			return (1);
		if (current->next)
			close(fd);
	}
	if (!current->next)
		go = dup2(fd, STDIN_FILENO);
	else
		go = 0;
	close (fd);
	return (go);
}

int	ft_init_last(t_node *output, int uni)
{	
	int		fd;
	t_node	*current;
	int		ret;

	ret = 0;
	current = output;
	if (current->flag == 1)
		fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(current->file);
		return (1);
	}
	if (current->next != NULL)
		ret = 0;
	else if (uni == 0)
		ret = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (ret == -1)
		return (ret);
	return (0);
}
