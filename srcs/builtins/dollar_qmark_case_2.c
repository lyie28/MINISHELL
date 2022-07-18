/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_qmark_case_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:43:16 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/13 11:24:14 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_get_size_dol(t_exetrio *exe, char *str)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = 0;
	temp = NULL;
	temp = ft_itoa(g_exit_code);
	exe->len_exit = ft_strlen(temp);
	free(temp);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			len += exe->len_exit;
			i++;
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*ft_replace_w_exitcode(int j, char *new)
{
	char	*exit;
	int		k;

	k = 0;
	exit = ft_itoa(g_exit_code);
	while (exit[k])
		new[j++] = exit[k++];
	new[j] = '\0';
	free(exit);
	return (new);
}
