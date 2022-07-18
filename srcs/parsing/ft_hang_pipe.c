/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hang_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:59:51 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/13 14:42:40 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_hang(char *str)
{
	char		c;
	t_quotes	*box;

	c = 0;
	box = ft_init_quotes();
	while (str[box->i])
	{
		if (str[box->i] == '\'' || str[box->i] == '\"')
			box->in_quotes = ft_in_quotes(str[box->i], box->quotes);
		else if (str[box->i] == '|' && box->in_quotes == 0)
			c = str[box->i];
		else if (str[box->i] != ' ')
			c = 0;
		box->i++;
	}
	free(box);
	if (c == '|')
		return (1);
	return (0);
}

int	ft_content_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_check_lesserone(t_exetrio *exe, char *end)
{
	g_exit_code = 2;
	free(end);
	printf("termicool found an unexpected EOF");
	exe->hang = -1;
	return (NULL);
}

static int	ft_exit_code_end(char *end, int copy)
{
	if (g_exit_code == 130)
	{
		free(end);
		return (1);
	}
	g_exit_code = copy;
	return (0);
}

char	*ft_hang_pipe(char *str, t_exetrio *exe)
{
	char	*end;
	char	*new;
	int		check[2];

	check[0] = 1;
	end = NULL;
	check[1] = g_exit_code;
	g_exit_code = 129;
	while (check[0] != 0 && ft_content_check(end) == 1)
	{
		if (end)
		{
			g_exit_code = check[1];
			free(end);
			end = NULL;
		}
		check[0] = get_next_line_mod(0, &end, 1);
	}
	if (ft_exit_code_end(end, check[1]) == 1)
		return (NULL);
	if (check[0] < 1)
		return (ft_check_lesserone(exe, end));
	new = ft_strjoin(str, end);
	free(end);
	return (new);
}
