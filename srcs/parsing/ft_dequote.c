/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 12:39:01 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 14:23:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/minishell.h"

static int	ft_cn_overflow(char *str, char ting)
{
	int	i;
	int	q;

	q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ting)
			q++;
		if (str[i] != ting)
			break ;
		i++;
	}
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == ting)
			q++;
		if (str[i] != ting)
			break ;
		i--;
	}
	return (q);
}

static char	*ft_create_new(char *str, char ting)
{
	int		size;
	int		x;
	int		q;
	int		offset;
	char	*new;

	x = 0;
	q = ft_cn_overflow(str, ting);
	size = ft_strlen(str) - q;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
	{
		ft_error("Malloc failed\n", 1);
		return (NULL);
	}
	while (str[x] == ting)
		x++;
	offset = x;
	while (x < (size + offset) && str[x])
	{
		new[x - offset] = str[x];
		x++;
	}
	new[x - offset] = '\0';
	return (new);
}

static int	ft_get_rows(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
	{
		i++;
	}
	return (i);
}

static int	ft_dequote_crossroads(char **split, char **new, int i)
{
	if (split[i][0] == '\"' || split[i][0] == '\'')
	{
		if (ft_dq_not_only(split[i]) == 0)
		{
			new[i] = ft_create_new(split[i], split[i][0]);
			if (!new[i])
			{
				free_double(new);
				free_double(split);
				return (1);
			}
		}
		else
			new[i] = ft_strdup(split[i]);
	}
	else
		new[i] = ft_strdup(split[i]);
	free(split[i]);
	return (0);
}

char	**ft_dequote(char **split)
{
	int		i;
	char	**new;
	int		rows;

	i = -1;
	if (!split)
		return (NULL);
	rows = ft_get_rows(split);
	new = malloc(sizeof(char *) * (rows + 1));
	if (!new)
	{
		ft_error("Malloc failed\n", 1);
		free_double(split);
		return (NULL);
	}
	while (split[++i])
	{
		if (ft_dequote_crossroads(split, new, i) == 1)
			return (NULL);
	}
	new[i] = NULL;
	free(split);
	return (new);
}
