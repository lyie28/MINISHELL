/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:10:44 by lyie              #+#    #+#             */
/*   Updated: 2021/10/19 16:43:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*ft_freerows_split(char **split, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static int	ft_getlen(const char *str, char sep, int quotes[2])
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (str[i] && (str[i] != sep || in_quotes == 1))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				quotes[0]++;
			else
				quotes[1]++;
			if (quotes[0] % 2 != 0 || quotes[1] % 2 != 0)
				in_quotes = 1;
			else if (quotes[1] % 2 == 0)
				in_quotes = 0;
			else
				in_quotes = 1;
		}
		i++;
	}
	return (i);
}

static int	ft_wordcount(const char *str, char sep)
{
	t_quotes	*box;
	int			count;

	if (str[0] == '\0')
		return (0);
	box = ft_init_quotes();
	while ((str[box->i]) && str[box->i] == sep)
		(box->i)++;
	while (str[box->i])
	{
		if (str[box->i] == '\'' || str[box->i] == '\"')
			box->in_quotes = ft_in_quotes(str[box->i], box->quotes);
		if (str[(box->i)++] == sep && box->in_quotes == 0)
		{
			(box->count)++;
			while ((str[box->i]) && str[box->i] == sep)
				(box->i)++;
		}
	}
	if (str[(box->i) - 1] != sep)
		box->count++;
	count = box->count;
	free(box);
	return (count);
}

static char	**ft_fill(const char *str, char sep, char **split, int wc)
{
	int	len;
	int	row;
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	row = 0;
	i = 0;
	while (row < wc)
	{
		if (str[i] != sep)
		{
			len = (ft_getlen(&(str[i]), sep, quotes));
			split[row] = malloc(sizeof(char) * (len + 1));
			if (!(split[row]))
				return (ft_freerows_split(split, row));
			ft_strlcpy(split[row], (const char *)&(str[i]), (len + 1));
			split[row] = ft_dollar_check_split(split[row], &i, i + len - 1);
			row++;
		}
		i++;
	}
	split[wc] = NULL;
	return (split);
}

char	**ft_split_quotes(const char *s, char c)
{
	int		wc;
	char	**split;

	if (!(s))
		return (NULL);
	wc = ft_wordcount(s, c);
	split = malloc(sizeof(char *) * (wc + 1));
	if (!split)
		return (NULL);
	split[wc] = 0;
	split = ft_fill(s, c, split, wc);
	if (!split)
		return (NULL);
	return (split);
}
