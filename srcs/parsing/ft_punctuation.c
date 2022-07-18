/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punctuation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:03:53 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 16:38:24 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_multichecking(char *str, char c)
{
	int	i;
	int	match;

	i = 0;
	match = 0;
	while (str[i] && str[i] == c)
	{
		match++;
		if (c == '<' || c == '>')
		{
			if (ft_chevron_test(i, &str[i]) == 1)
				return (1);
		}
		if (match == 2 && c == '|')
			return (ft_error("multiples pipes not allowed\n", 1));
		else if (match == 3)
			return (ft_error("bad input\n", 1));
		i++;
	}
	return (0);
}

int	ft_check_multis(char *str, t_quotes *box)
{
	int	multi;

	multi = 0;
	while (str[box->i])
	{
		if (str[box->i] == '\'' || str[box->i] == '\"')
			box->in_quotes = ft_in_quotes(str[box->i], box->quotes);
		if ((str[box->i] == '<' || str[box->i] == '>') && box->in_quotes == 0)
			multi = ft_multichecking(&str[box->i], str[box->i]);
		else if (str[box->i] == '|' && box->in_quotes == 0)
			multi = ft_multichecking(&str[box->i], str[box->i]);
		if (multi == 1)
			return (1);
		box->i++;
	}
	return (0);
}

static void	ft_init_box(t_quotes *box)
{
	box->hang = 0;
	box->start = 0;
	box->punc = 0;
	box->pipe_flag = 0;
}

int	ft_check_words(char *str, t_exetrio *exe, t_quotes *box)
{
	ft_init_box(box);
	while (str[box->i])
	{
		if (str[box->i] == '\'' || str[box->i] == '\"')
			box->in_quotes = ft_in_quotes(str[box->i], box->quotes);
		if ((str[box->i] == '<' || str[box->i] == '>') && box->in_quotes == 0)
			ft_punc_chevrons(str, box);
		else if (str[box->i] == '|' && box->in_quotes == 0)
		{
			if (ft_punc_pipe(str, box) == 1)
				return (1);
		}
		else if (str[box->i] != ' ')
			ft_punc_space(box);
		if (ft_punc_equal_two(str, box) == 1)
			return (1);
		if (str[box->i] != ' ' && str[box->i] != '|')
			box->pipe_flag = 0;
		box->i++;
	}
	if (ft_chevrons_before(str, box) == 1)
		return (1);
	if (box->hang == 1)
		exe->hang = 1;
	return (0);
}

int	ft_punctuation(char *str, t_exetrio *exe)
{
	t_quotes	*box;

	box = ft_init_quotes();
	if (ft_unclosed(str) == 1)
		return (ft_excode_two(box));
	if (ft_check_multis(str, box) == 1)
	{
		free(box);
		if (g_exit_code == 3)
			g_exit_code = 1;
		else
			g_exit_code = 2;
		return (1);
	}
	free(box);
	box = ft_init_quotes();
	if (ft_check_words(str, exe, box) == 1)
		return (ft_excode_two(box));
	free(box);
	return (0);
}
