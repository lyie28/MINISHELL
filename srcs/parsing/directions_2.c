/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:42:59 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 11:28:38 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/minishell.h"

int	ft_is_this(char *targets, char c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (targets[i])
	{
		if (c == targets[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_parse_skipper(char *pipeline, int *x)
{
	int	i;

	i = *x;
	if (ft_is_this("<>", pipeline[i]))
		i++;
	if (ft_is_this("<>|", pipeline[i]))
		return (ft_error("ERROR but need to sort out frees and exit here\n", 1));
	while (ft_is_this(" ", pipeline[i]))
		i++;
	if (ft_is_this("<>|", pipeline[i]))
		return (ft_error("ERROR but need to sort out frees and exit here\n", 1));
	while ((pipeline[i]) && (ft_is_this("<>| ", pipeline[i]) == 0))
		i++;
	while ((ft_is_this(" ", pipeline[i]) == 1))
		i++;
	*x = i;
	return (0);
}

int	ft_copy_to_list(char *pipeline, t_list *list, int here, int uni)
{
	int		size;
	char	*file;
	int		i;
	t_node	*node_in;

	i = 0;
	size = 0;
	node_in = NULL;
	while (pipeline[size] && (ft_is_this("<>| ", pipeline[size]) == 0))
		size++;
	file = malloc(sizeof(char) * (size + 1));
	if (!file)
		return (-1);
	while (pipeline[i] && (ft_is_this("<>| ", pipeline[i]) == 0))
	{
		file[i] = pipeline[i];
		i++;
	}
	file[i] = '\0';
	node_in = ft_lstnew(file, here, uni);
	ft_lstadd_back(list, node_in);
	return (0);
}

int	ft_skipper(int *i, char *pipeline, char *one, char *two)
{
	int	flag;

	flag = 0;
	(*i)++;
	if (ft_is_this(one, pipeline[(*i)]))
	{
		(*i)++;
		flag = 1;
	}
	if ((pipeline[(*i)]) && ft_is_this(two, pipeline[(*i)]))
		(*i)++;
	while ((pipeline[*i]) && ft_is_this(" ", pipeline[(*i)]))
		(*i)++;
	return (flag);
}

int	ft_space_cutter(char *str)
{
	int	i;
	int	count;

	i = ft_strlen(str) - 1;
	count = 0;
	while (str[i])
	{
		if (ft_is_this(" ", str[i]) == 1)
			count++;
		else
			return (count);
		i++;
	}
	return (count);
}
