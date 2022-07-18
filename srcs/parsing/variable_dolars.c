/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_dolars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:27:06 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/12 16:56:43 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_dollar_is_valid(char *str, int i)
{
	int		nb_quotes;
	char	c;

	c = '\'';
	nb_quotes = 0;
	while (i >= 0)
	{
		if (str[i] == c)
			nb_quotes++;
		i--;
	}
	if (nb_quotes % 2 == 0)
		return (1);
	return (0);
}

int	ft_check_nb_dollars(char *str)
{
	int		i;
	int		c;
	int		nb;
	char	*to_check;

	c = '$';
	i = 0;
	nb = 0;
	to_check = NULL;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != '?')
		{
			to_check = ft_substr(str, 0, i);
			if (ft_dollar_is_valid(to_check, i) == 1)
				nb++;
			free(to_check);
			to_check = NULL;
		}	
		i++;
	}
	if (str[i] == c)
		nb++;
	return (nb);
}

void	ft_init_svar(t_var *v, char *str)
{
	v->new = NULL;
	v->var = NULL;
	v->value = NULL;
	v->s = 0;
	v->j = 0;
	v->len_tot = ft_strlen(str);
	v->len_var = 0;
	v->len_value = 0;
	v->quotes = 0;
	v->i = -1;
}
