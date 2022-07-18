/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:42:59 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 12:56:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/minishell.h"

static void	ft_pipeline_skipper(char *pipeline, int	*x)
{
	int	i;

	i = *x;
	while (pipeline[i] && (ft_is_this("<>| ", pipeline[i]) == 0))
		i++;
	while (pipeline[i] && (ft_is_this(" ", pipeline[i]) == 1))
		i++;
	*x = i;
}

void	ft_new_pipeline_out(int size, char *pipeline, char *new, t_list *list)
{
	t_quotes	*box;

	box = ft_init_quotes();
	while (pipeline[box->i])
	{
		if (pipeline[box->i] == '\'' || pipeline[box->i] == '\"')
			box->in_quotes = ft_in_quotes(pipeline[box->i], box->quotes);
		if (pipeline[box->i] == '>' && box->in_quotes == 0)
		{
			if (!pipeline[box->i])
				break ;
			box->flag = ft_skipper(&box->i, pipeline, ">", "<");
			if (ft_is_this("<>| ", pipeline[box->i]) == 0)
			{
				ft_copy_to_list(&pipeline[box->i], list, box->flag, 0);
				ft_pipeline_skipper(pipeline, &box->i);
			}
		}
		else if (box->count < size)
			new[(box->count)++] = pipeline[(box->i)++];
		else
			(box->i)++;
	}
	new[box->count] = '\0';
	free(box);
}

static void	ft_new_pipeline_loop(char *pipeline, t_quotes *box, t_list *list)
{
	if (pipeline[box->i] == '<' && pipeline[box->i + 1]
		&& pipeline[box->i + 1] == '>')
	{
		box->np_uni = 1;
		box->np_stock = box->i + 1;
	}
	box->flag = ft_skipper(&box->i, pipeline, "<", ">");
	ft_copy_to_list(&pipeline[box->i], list, box->flag, box->np_uni);
	if (box->np_uni == 0)
		ft_pipeline_skipper(pipeline, &box->i);
	else
		box->i = box->np_stock;
}

void	ft_new_pipeline(int size, char *pipeline, char *new, t_list *list)
{
	t_quotes	*box;

	box = ft_init_quotes();
	while (pipeline[box->i])
	{
		box->np_uni = 0;
		box->np_stock = 0;
		if (pipeline[box->i] == '\'' || pipeline[box->i] == '\"')
			box->in_quotes = ft_in_quotes(pipeline[box->i], box->quotes);
		if (pipeline[box->i] == '<' && box->in_quotes == 0)
			ft_new_pipeline_loop(pipeline, box, list);
		else if (box->count < size)
			new[(box->count)++] = pipeline[(box->i)++];
		else
			(box->i)++;
	}
	new[box->count] = '\0';
	free(box);
}

char	*ft_input_sorter(char *pipeline, t_exetrio exe)
{
	char	*new_pipeline;
	char	*new_pipeline2;
	char	*new_pipeline3;
	int		size;

	new_pipeline = NULL;
	new_pipeline = ft_dollars(exe, pipeline, new_pipeline);
	free(pipeline);
	ft_fill_direction_list(&exe, new_pipeline);
	size = ft_get_size(new_pipeline);
	new_pipeline2 = malloc(sizeof(char) * size + 1);
	if (!new_pipeline2)
		return (ft_free_pipeline(new_pipeline));
	ft_new_pipeline(size, new_pipeline, new_pipeline2, exe.input);
	free(new_pipeline);
	size = ft_get_size_out(new_pipeline2);
	new_pipeline3 = malloc(sizeof(char) * size + 1);
	if (!new_pipeline3)
		return (ft_free_pipeline(new_pipeline3));
	ft_new_pipeline_out(size, new_pipeline2, new_pipeline3, exe.output);
	free(new_pipeline2);
	return (new_pipeline3);
}
