/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:56:00 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/19 14:28:33 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_in_sing_quotes_loop(char *str, int x, t_qbis *q)
{
	int	i;

	i = 0;
	q->dub = 0;
	q->sing = 0;
	while (str[i] && i < x)
	{
		if (str[i] == '\'' && q->dub % 2 == 0)
			q->sing++;
		if (str[i] == '\"' && (q->sing % 2 == 0))
			q->dub++;
		i++;
	}
}

int	ft_in_sing_quotes(char *str, int x, t_qbis *q)
{
	if (x == 0)
		return (0);
	if (x == 1 && str[0] != '\"')
		return (0);
	ft_in_sing_quotes_loop(str, x, q);
	if (q->dub % 2 == 0)
	{
		if (q->sing % 2 == 0)
			return (0);
		else
			return (1);
	}
	else if (q->sing % 2 == 0)
		return (0);
	return (1);
}

static char	*ft_fill_str_quotes(char *old, char *new, t_qbis *q)
{
	q->sing = 0;
	q->dub = 0;
	q->i = 0;
	q->j = 0;
	while (old[q->i])
	{
		if (old[q->i] == '\'' && q->dub % 2 == 0)
		{
			q->i++;
			q->sing++;
		}
		else if (old[q->i] == '\"' && (q->sing % 2 == 0))
		{
			q->dub++;
			q->i++;
		}
		else
		{
			new[q->j] = old[q->i];
			q->i++;
			q->j++;
		}
	}
	new[q->j] = '\0';
	return (new);
}

static int	ft_get_nb_q(char *str)
{
	int	i;
	int	dub;
	int	sing;

	sing = 0;
	i = 0;
	dub = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dub % 2 == 0)
			sing++;
		if (str[i] == '\"' && (sing % 2 == 0))
			dub++;
		i++;
	}
	return (dub + sing);
}

char	*ft_new_str_quotes(char *old)
{
	int		len;
	int		i;
	char	*new;
	t_qbis	q;

	i = 0;
	len = ft_strlen(old);
	len = len - ft_get_nb_q(old);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	new = ft_fill_str_quotes(old, new, &q);
	return (new);
}
