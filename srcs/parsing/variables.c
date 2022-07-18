/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:51:33 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/19 16:16:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_if_dollars(t_exetrio *exe, char *s, int i, t_var *v)
{
	int	x;

	i++;
	v->s = i;
	while (s[v->s] != '\'' && s[v->s] != '\"' && s[v->s] != ' '
		&& s[v->s] != '\0' && s[v->s] != '$' && s[v->s] != '='
		&& s[v->s] != '+' && s[v->s] != '/')
		v->s++;
	v->var = ft_substr(s, i, v->s - i);
	v->len_var = ft_strlen(v->var) + 1;
	v->value = ft_check_value_for_label(exe, v->var);
	i--;
	if (v->value)
	{
		x = -1;
		while (v->value[++x])
		{
			v->new[v->j] = v->value[x];
			v->j++;
		}
	}
	i += v->len_var;
	if (v->var)
		free(v->var);
	return (i);
}

static int	ft_no_dollars(char *str, int i, t_var *v)
{
	v->new[v->j] = str[i];
	i++;
	v->j++;
	return (i);
}

char	*ft_str_w_variables(t_exetrio *exe, t_var *v, char *s, t_qbis *q)
{
	int	i;
	int	tp;

	i = 0;
	if (ft_malloc_vnew(v) == 0)
		return (NULL);
	while (s[i])
	{
		if (i == 0)
			tp = 0;
		else
			tp = 1;
		if (s[i] == '$' && !s[i + 1])
			return (ft_free_new(s, v));
		if ((s[i] == '$' && s[i + 1] == '?') || (s[i] == '$'
				&& s[i - tp] != '\"' && s[i + 1] == '?' && s[i + 2] != '\"'))
			return (ft_free_new(s, v));
		else if (s[i] == '$' && ft_in_sing_quotes(s, i, q) == 0)
			i = ft_if_dollars(exe, s, i, v);
		else
			i = ft_no_dollars(s, i, v);
	}
	v->new[v->j] = '\0';
	return (v->new);
}

char	*ft_get_tab_variables(t_exetrio *exe, char *str)
{
	char	*new_str;
	t_var	var;
	t_qbis	q;

	new_str = NULL;
	if ((str[0] == '$' && str[1] == '\0')
		|| (str[0] == '$' && str[1] == ' '))
	{
		new_str = ft_strdup("$");
		return (new_str);
	}
	else if (dol_alone(str) == 1)
		return (str);
	ft_init_svar(&var, str);
	ft_v_counter(exe, &var, str, &q);
	var.s = 0;
	new_str = ft_str_w_variables(exe, &var, str, &q);
	return (new_str);
}
