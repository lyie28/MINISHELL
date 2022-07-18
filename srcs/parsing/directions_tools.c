/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:49:20 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/10/19 16:08:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_dollars(t_exetrio exe, char *pipeline, char *new_pipeline)
{
	int		dollars;
	char	*temp;

	dollars = ft_check_nb_dollars(pipeline);
	if (dollars)
	{
		temp = ft_strdup(pipeline);
		new_pipeline = ft_get_tab_variables(&exe, temp);
		if (ft_strcmp(temp, new_pipeline) != 0)
			free(temp);
	}
	else
		new_pipeline = ft_strdup(pipeline);
	return (new_pipeline);
}

char	*ft_free_pipeline(char *pipe)
{
	free(pipe);
	return (NULL);
}
