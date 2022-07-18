/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:41:27 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 15:56:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_front(t_node *head, t_node *new)
{
	new->next = head;
	head = new;
}

int	ft_str_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_got_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	ft_frees_in_main(t_exetrio exe, char *possible_free)
{
	if (possible_free)
		free(possible_free);
	free(exe.input);
	free(exe.output);
	free(exe.direction);
	if (exe.str)
		free(exe.str);
}

void	ft_swap(char **d1, char **d2)
{
	char	*tmp;

	tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}
