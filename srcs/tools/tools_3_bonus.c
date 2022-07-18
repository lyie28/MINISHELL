/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:43:08 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 14:10:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_ending(t_exetrio *exe)
{
	if (exe->input)
		free(exe->input);
	if (exe->output)
		free(exe->output);
	if (exe->direction)
		free(exe->direction);
	if (exe->pipefd)
		ft_free_pipes(exe->pipefd);
	return (g_exit_code);
}

void	free_loop(t_exetrio *exe)
{
	if (exe->path)
		free((char *)exe->path);
	if (exe->command)
		free_double((char **)exe->command);
	if (exe->tab_env)
		free_tab(exe->tab_env);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	if (str != NULL)
		free(str);
}

/* FREE ALL ENV LISTS: t_list e and tab_env */
int	ft_piperr(t_exetrio	*exe, char *error, int ret)
{
	ft_freelist(exe->output->head);
	ft_freelist(exe->input->head);
	free(exe->input);
	free(exe->output);
	free_double(exe->cmd_str);
	free_double(exe->cmd);
	ft_free_pipes(exe->pipefd);
	write(2, error, ft_strlen(error));
	return (ret);
}

int	ft_strcmp_diff(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
