/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello_doc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:41:25 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 15:33:56 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/minishell.h"
#include <unistd.h>
#include <fcntl.h>

static int	ft_setup(char *file, int *count, int fd[2])
{
	g_exit_code = 129;
	fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd[0] = open(file, O_RDONLY, 0644);
	if (!fd[1] || !fd[0])
		return (-1);
	(*count) = 0;
	return (0);
}

static int	close_free_error(int fd, char *line, int **pipefd, char *error)
{
	ft_error(error, 1);
	ft_free_pipes(pipefd);
	close(fd);
	free(line);
	exit (-1);
}

static int	close_all_good(int fd[2], char *line, int **pipefd, int copy)
{
	g_exit_code = copy;
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		close_free_error(fd[0], line, pipefd, "dup2 failed\n");
	close(fd[0]);
	free(line);
	return (0);
}

static int	ft_finish_heredoc(int copy)
{
	if (g_exit_code == 130)
		return (-2);
	g_exit_code = copy;
	write(2, "Termicool: warning: « here-document » unexpected EOF\n", 56);
	return (0);
}

/*issue with signals returning Malloc failed,
 * do malloc error in GNL and just exit*/
int	here_doc(char *del, char *file, int **pipefd)
{
	int		fd[2];
	char	*line;
	int		count;
	int		copy;

	copy = g_exit_code;
	line = NULL;
	count = 0;
	if (ft_setup(file, &count, fd) == -1)
		return (-1);
	while (get_next_line(0, &line, 2) > 0)
	{
		if (ft_strncmp(line, del, sizeof(del)) == 0)
			return (close_all_good(fd, line, pipefd, copy));
		if (count != 0)
			write(fd[1], "\n", 1);
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
		count++;
	}
	if (line)
		free(line);
	return (ft_finish_heredoc(copy));
}
