/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequote_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 12:39:01 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 15:10:41 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_nbquotes(char *str, char ting)
{
	int	q;
	int	z;

	q = 0;
	z = 0;
	while (str[q])
	{
		if (str[q] == ting)
			z++;
		q++;
	}
	return (z);
}

static char	*ft_create_new(char *str, char ting)
{
	int		size;
	int		x;
	int		q;
	char	*new;

	x = 0;
	q = 0;
	while (str[q] == ting)
		q++;
	size = (ft_strlen(str) - ft_nbquotes(str, ting));
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (x < size && str[q])
	{
		new[x] = str[x + q];
		x++;
	}
	new[x] = '\0';
	return (new);
}

static int	ft_get_rows(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		i++;
	}
	return (i);
}

char	**ft_dequote_export(char **split)
{
	int		i;
	int		j;
	char	**new;
	int		rows;
	int		quotes;

	i = 0;
	j = 0;
	quotes = 0;
	rows = ft_get_rows(split);
	new = malloc(sizeof(char *) * (rows + 1));
	if (!new)
		return (NULL);
	while (split[i])
	{
		if (split[i][0] == '\"' || split[i][0] == '\'')
			new[i] = ft_create_new(split[i], split[i][0]);
		else
			new[i] = ft_strdup(split[i]);
		free(split[i]);
		i++;
	}
	new[i] = NULL;
	free(split);
	return (new);
}
