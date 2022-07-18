/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:42 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 15:17:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_counter_overflow(char *s, t_var *v, t_counter *n, t_exetrio *exe)
{
	char	*temp1;
	char	*temp2;

	temp1 = NULL;
	temp2 = NULL;
	n->i++;
	v->s = n->i;
	while (s[v->s] != '\'' && s[v->s] != '\"' && s[v->s] != ' '
		&& s[v->s] != '\0' && s[v->s] != '$' && s[v->s] != '='
		&& s[v->s] != '+' && s[v->s] != '/')
		v->s++;
	temp1 = ft_substr(s, n->i, v->s - n->i);
	temp2 = ft_check_value_for_label(exe, temp1);
	n->i += ft_strlen(temp1);
	n->count = n->count + ft_strlen(temp2);
	free(temp1);
}

static int	ft_free_ret_counter(t_counter *this, int ret)
{
	int	ret1;

	ret1 = ret;
	free(this);
	return (ret1);
}

static void	ft_increment_counters(t_counter *n)
{
	n->i++;
	n->count++;
}

static void	ft_set_tp(t_counter *n)
{
	if (n->i == 0)
		n->count = 0;
	if (n->i == 0)
		n->tp = 0;
	else
		n->tp = 1;
}

int	ft_v_counter(t_exetrio *exe, t_var *v, char *s, t_qbis *q)
{
	t_counter	*n;

	n = malloc(sizeof (t_counter));
	if (!n)
		return (ft_error("malloc failed\n", 0));
	n->i = 0;
	if (!s[n->i])
		return (ft_free_ret_counter(n, 0));
	while (s[n->i])
	{
		ft_set_tp(n);
		if (s[n->i] == '$' && !s[n->i + 1])
			return (ft_free_ret_counter(n, 1));
		if ((s[n->i] == '$' && s[n->i + 1] == '?')
			|| (s[n->i] == '$' && s[n->i - n->tp]
				!= '\"' && s[n->i + 1] == '?' && s[n->i + 2] != '\"'))
			return (ft_free_ret_counter(n, 1));
		else if (s[n->i] == '$' && ft_in_sing_quotes(s, n->i, q) == 0)
			ft_counter_overflow(s, v, n, exe);
		else
			ft_increment_counters(n);
	}
	v->s = 0;
	v->len_tot = n->count;
	return (ft_free_ret_counter(n, n->count));
}
