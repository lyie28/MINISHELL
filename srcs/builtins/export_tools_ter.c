/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools_ter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:55:30 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/16 11:55:32 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_sortlst_alpha(t_list *lst)
{
	t_node	*elem1;
	t_node	*elem2;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		elem1 = lst->head;
		elem2 = lst->head->next;
		swapped = 0;
		while (elem2)
		{
			if (ft_strcmp_diff(elem1->label, elem2->label) > 0)
			{
				ft_swap(&(elem1->label), &(elem2->label));
				ft_swap(&(elem1->value), &(elem2->value));
				swapped = 1;
			}
			elem1 = elem1->next;
			elem2 = elem2->next;
		}
	}
}

int	check_quotes(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[i + 1])
	{
		if (str[i] == '"' && str[i + 1] == '\'')
			return (0);
	}
	if (str[i] == c)
		j++;
	while (str[i])
		i++;
	if (str[i] == c)
		j++;
	return (j);
}

static int	get_nb_q(char *str, char c)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == c)
			q++;
		i++;
	}
	return (q);
}

static char	*get_value(char *tmp, char *value, char c)
{
	int	q;

	q = 0;
	q = get_nb_q(tmp, c);
	value = ft_substr(tmp, q / 2, ft_strlen(tmp) - q);
	free(tmp);
	return (value);
}

char	*parsing_quotes(char *str, int pos)
{
	char	*tmp;
	char	*value;
	int		i;
	int		q;

	i = 0;
	q = 0;
	value = NULL;
	if (!str[pos + 1])
	{
		value = ft_strdup("\"\"");
		return (value);
	}
	tmp = ft_substr(str, pos + 1, ft_strlen(str) - pos);
	if (check_quotes(tmp, '\'') > 0)
		return (get_value(tmp, value, '\''));
	else if (check_quotes(tmp, '"') > 0)
		return (get_value(tmp, value, '"'));
	else
	{
		value = ft_strdup(tmp);
		free(tmp);
		return (value);
	}
	return (NULL);
}
