/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:33:59 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 13:40:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	ft_get_size_overflow(char *pipeline, t_quotes *box)
{
	if (pipeline[box->i] == '<' && pipeline[box->i + 1]
		&& pipeline[box->i + 1] == '>')
		box->np_stock = box->i + 1;
	box->i++;
	if (box->np_stock == 0)
	{
		if (ft_parse_skipper(pipeline, &box->i))
		{
			free(box);
			exit (1);
		}
	}
	else
		box->i = box->np_stock;
}

/*returns size of string without input which is sent to input list*/
int	ft_get_size(char *pipeline)
{
	t_quotes	*box;
	int			ret;

	box = ft_init_quotes();
	while (pipeline[box->i])
	{
		box->np_stock = 0;
		if (pipeline[box->i] == '\'' || pipeline[box->i] == '\"')
			box->in_quotes = ft_in_quotes(pipeline[box->i], box->quotes);
		if (ft_is_this("<", pipeline[box->i]) && box->in_quotes == 0)
			ft_get_size_overflow(pipeline, box);
		else
		{
			box->count++;
			box->i++;
		}
	}
	ret = box->count;
	free(box);
	return (ret);
}

int	ft_get_size_out(char *pipeline)
{
	int	i;
	int	count;
	int	quotes[2];
	int	in_quotes;

	in_quotes = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	count = 0;
	while (pipeline[i])
	{
		if (pipeline[i] == '\'' || pipeline[i] == '\"')
			in_quotes = ft_in_quotes(pipeline[i], quotes);
		if (ft_is_this(">", pipeline[i++]) && in_quotes == 0)
		{
			if (ft_parse_skipper(pipeline, &i) == 1)
				exit(1);
		}
		else
			count++;
	}
	return (count);
}

void	ft_fill_direction_list(t_exetrio *exe, char *str)
{
	char		c;
	t_quotes	*box;
	t_charnode	*current;
	int			i;

	i = 0;
	current = NULL;
	box = ft_init_quotes();
	while (str[box->i])
	{
		if (str[box->i] == '\'' || str[box->i] == '\"')
			box->in_quotes = ft_in_quotes(str[box->i], box->quotes);
		if ((str[box->i] == '<' || str[box->i] == '>') && box->in_quotes == 0)
		{
			c = str[box->i];
			current = ft_lstnew_char(c);
			ft_lstadd_back_char(exe->direction, current);
			while (str[box->i] == c)
				box->i++;
		}
		else
			box->i++;
	}
	free(box);
}

t_quotes	*ft_init_quotes(void)
{
	t_quotes	*box;

	box = malloc(sizeof(t_quotes));
	if (!box)
		return (NULL);
	box->i = 0;
	box->flag = 0;
	box->quotes[0] = 0;
	box->quotes[1] = 0;
	box->in_quotes = 0;
	box->count = 0;
	box->np_stock = 0;
	return (box);
}
