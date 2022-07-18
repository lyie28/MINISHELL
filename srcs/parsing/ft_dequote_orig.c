/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequote_orig.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 12:39:01 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 18:03:59 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**ft_dequote_orig(char **split)
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
		new[i] = ft_new_str_quotes(split[i]);
		free(split[i]);
		i++;
	}
	new[i] = NULL;
	free(split);
	return (new);
}
