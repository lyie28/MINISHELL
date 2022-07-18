/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:40:42 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 11:51:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/minishell.h"
#include <fcntl.h>

static int	ft_freeret(char *chest)
{
	if (chest != NULL)
		free(chest);
	return (-1);
}

static int	ft_nline(char **line, char **chest, int i, int size)
{
	(*line) = malloc(sizeof(char) * i + 1);
	if (!(*line))
		return (-1);
	ft_strlcpy((*line), (*chest), i + 1);
	(*chest) = ft_substr_gnl((*chest), i + 1, (size - i));
	if (!(*chest))
	{
		free(*chest);
		return (-1);
	}
	free(*chest);
	*chest = NULL;
	return (1);
}

static int	ft_endfile(char **line, char **chest)
{
	int	i;
	int	size;

	size = ft_strlen(*chest);
	i = (ft_strchr(*chest, '\n'));
	if (i != -1)
		return (ft_nline(line, chest, i, size));
	else if (ft_strlen(*chest) != 0)
	{
		(*line) = ft_strdup(*chest);
		if (!(*line))
		{
			free(*chest);
			return (-1);
		}
	}
	(*line) = ft_strdup("");
	if (!(*line))
	{
		free(*chest);
		return (-1);
	}
	free(*chest);
	*chest = NULL;
	return (0);
}

static int	ft_nullify(char **line, char **chest)
{
	if (!(*chest))
	{
		(*line) = ft_strdup("");
		if (!(*line))
			return (-1);
		return (0);
	}
	return (ft_endfile(line, chest));
}

int	get_next_line_mod(int fd, char **line, int BUFFER_SIZE)
{
	static char	*chest;
	int			i;
	int			store;
	int			size;
	char		buffer[1000];

	i = 0;
	size = 0;
	ft_bzero(buffer, 1000);
	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0 || !line)
		return (-1);
	store = (read(fd, buffer, BUFFER_SIZE));
	while (store > 0)
	{
		chest = ft_get_strjoin(chest, buffer, store);
		if (!chest)
			return (ft_freeret(chest));
		size = ft_strlen(chest);
		i = (ft_strchr(chest, '\n'));
		if (i != -1)
			return (ft_nline(line, &chest, i, size));
		store = (read(fd, buffer, BUFFER_SIZE));
	}
	return (ft_nullify(line, &chest));
}
