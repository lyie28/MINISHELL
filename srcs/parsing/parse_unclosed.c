/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:03:53 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 14:13:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*sort out with frees*/
int	ft_unclosed(char *str)
{
	t_quotes	*box;

	box = ft_init_quotes();
	while (str[box->i])
	{
		if (str[box->i] == '\"')
		{
			if (box->quotes[1] % 2 == 0)
				box->in_quotes = 1;
			else
				box->in_quotes = 0;
			box->quotes[1]++;
		}
		if (str[box->i] == '\'' && box->in_quotes == 0)
			box->quotes[0]++;
		(box->i)++;
	}
	if (box->quotes[0] % 2 != 0 || box->quotes[1] % 2 != 0)
	{
		free(box);
		printf("Double or single quotes not closed\n");
		return (1);
	}
	free(box);
	return (0);
}
