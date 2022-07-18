/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_qmark_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:43:16 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/13 11:24:14 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_free_stuff(char *str, char *exit)
{
	free (str);
	free (exit);
}

static char	*ft_replace_exitcode(char *str, int len)
{
	int		i;
	int		j;
	char	*new;
	char	*exit;

	i = 0;
	j = 0;
	exit = ft_itoa(g_exit_code);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			new = ft_replace_w_exitcode(j, new);
			j += ft_strlen(exit);
			i += 2;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	ft_free_stuff(str, exit);
	return (new);
}

static void	if_get_ret(t_exetrio *exe, int get_ret, int j)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (get_ret == 1)
	{
		len = ft_get_size_dol(exe, exe->cmd[j]);
		exe->cmd[j] = ft_replace_exitcode(exe->cmd[j], len);
	}
}

static int	ft_echo_get_ext(t_exetrio *exe, int j, int i)
{
	char	*temp;

	temp = NULL;
	if (ft_strlen(exe->cmd[j]) == 4)
	{
		temp = ft_substr(exe->cmd[j], i, 4);
		if (ft_strcmp(temp, "'$?'") == 0)
		{
			free(temp);
			return (1);
		}
		free(temp);
	}
	return (0);
}

void	ft_echo_get_return(t_exetrio *exe)
{
	int		i;
	int		j;
	int		get_ret;

	get_ret = 0;
	j = -1;
	if (!exe->cmd)
		return ;
	while (exe->cmd[++j])
	{
		i = -1;
		while (exe->cmd[j][++i])
		{
			if (exe->cmd[j][i + 1] != '\0' && (exe->cmd[j][i] == '$'
						&& (exe->cmd[j][i + 1] == '?')))
				get_ret = 1;
			if (exe->cmd[j][i] == '\'')
			{
				if (ft_echo_get_ext(exe, j, i) == 1)
					return ;
			}
		}
		if_get_ret(exe, get_ret, j);
	}
}
