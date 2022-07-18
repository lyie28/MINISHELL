/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directing_stuff_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:28:27 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 11:46:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void	ft_diamond(t_dir_tools *tools)
{
	tools->prev = tools->in;
	tools->temp = tools->temp->next;
	tools->uni = 1;
}
