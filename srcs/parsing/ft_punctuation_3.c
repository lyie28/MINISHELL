/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punctuation_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:29:36 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/13 16:54:59 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_dollar_test(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == ' ' || str[j] == '$')
			j++;
		else if (str[j] == '|')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	ft_chevron_test(int i, char *str)
{
	int	j;

	j = i;
	while (str[j])
	{
		if (str[j] == '$')
		{
			if (ft_dollar_test(&str[j]) == 1)
			{
				g_exit_code = 3;
				return (ft_error("Ambiguous redirection\n", 1));
			}
			j++;
		}
		else if (str[j] == ' ' || str[j] == '<' || str[j] == '>')
			j++;
		else
			return (0);
	}
	return (0);
}

int	ft_excode_two(t_quotes *box)
{
	free(box);
	g_exit_code = 2;
	return (1);
}
