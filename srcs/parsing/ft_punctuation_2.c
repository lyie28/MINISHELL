/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punctuation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:16:12 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/18 12:07:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_punc_chevrons(char *str, t_quotes *box)
{
	box->c = str[box->i];
	while (str[box->i] == box->c)
		box->i++;
	box->i--;
	box->punc++;
}

int	ft_punc_pipe(char *str, t_quotes *box)
{
	box->hang = 1;
	box->pipe_flag = 1;
	box->c = str[box->i];
	box->punc++;
	if (box->start != 1)
	{
		printf("unexpected symbol near to symbol %c\n", str[box->i]);
		return (1);
	}
	while (str[box->i] == box->c)
		box->i++;
	box->i--;
	return (0);
}

void	ft_punc_space(t_quotes *box)
{
	box->hang = 0;
	box->start = 1;
	box->punc = 0;
}

int	ft_punc_equal_two(char *str, t_quotes *box)
{
	if (box->punc == 2)
	{
		if (box->pipe_flag == 1 && str[box->i] != '|')
		{
			box->pipe_flag = 0;
			box->punc--;
		}
		else if (str[box->i] == '>' && str[box->i - 1]
			&& str[box->i - 1] == '<')
			box->punc--;
		else
		{
			printf("unexpected symbol near to symbol %c\n", box->c);
			return (1);
		}
	}
	return (0);
}

int	ft_chevrons_before(char *str, t_quotes *box)
{
	if (str[(box->i) - 1] == '>' || str[(box->i) - 1] == '<')
	{
		printf("unexpected symbol near to symbol newline\n");
		return (1);
	}
	return (0);
}
