/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:40:11 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 16:24:49 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_freerows(char **split, int row)
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

static int	ft_getlen(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static int	ft_wordcount(const char *str, char sep)
{
	int	i;
	int	row;

	if (!str[0])
		return (0);
	row = 0;
	i = 0;
	while ((str[i]) && str[i] == sep)
		i++;
	while (str[i])
	{
		if (str[i] == sep)
		{
			row++;
			i++;
			while ((str[i]) && str[i] == sep)
				i++;
		}
		else
			i++;
	}
	if (str[i - 1] != sep)
		row++;
	return (row);
}

static char	**ft_fill(const char *str, char sep, char **split, int wc)
{
	int	len;
	int	row;
	int	i;

	i = 0;
	row = 0;
	while (row < wc)
	{
		if (str[i] != sep)
		{
			len = (ft_getlen(&(str[i]), sep));
			split[row] = malloc(sizeof(char) * (len + 1));
			if (!(split[row]))
				return (ft_freerows(split, row));
			ft_strlcpy(split[row], (const char *)&(str[i]), (len + 1));
			row++;
			i = i + len - 1;
		}
		i++;
	}
	split[wc] = NULL;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	int		wc;
	char	**split;

	if (!(s))
		return (NULL);
	wc = ft_wordcount(s, c);
	split = malloc(sizeof(char *) * (wc + 1));
	if (!split)
		return (NULL);
	split = ft_fill(s, c, split, wc);
	if (!split)
		return (NULL);
	return (split);
}
