/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:27:46 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/15 18:04:41 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_get_values(t_exetrio *exe, t_var *v, char *str)
{
	v->var = ft_substr(str, v->i, v->s - v->i);
	v->len_var = ft_strlen(v->var) + v->quotes;
	v->value = ft_check_value_for_label(exe, v->var);
	if (v->value)
	{
		v->len_value = ft_strlen(v->value);
		v->len_tot = v->len_tot - (v->len_var) + v->len_value;
	}
	else
		v->len_tot = v->len_tot - (v->len_var);
	if (v->var)
		free(v->var);
}

char	*ft_check_value_for_label(t_exetrio *exe, char *str)
{
	t_node	*current;

	current = exe->e->head;
	while (current)
	{
		if (ft_strcmp(str, current->label) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	dol_alone(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == '$' && (str[i + 2] == ' '
				|| str[i + 2] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_free_new(char *str, t_var *v)
{
	free(v->new);
	v->new = NULL;
	return (str);
}

int	ft_malloc_vnew(t_var *v)
{
	v->new = malloc(sizeof(char) * (v->len_tot + 1));
	if (!v->new)
		return (0);
	return (1);
}
