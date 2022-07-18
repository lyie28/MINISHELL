/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequote_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:48:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 13:49:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/minishell.h"

int	ft_dq_not_only(char *str)
{
	int		i;
	char	*check;

	if (str[0] == '\"')
		check = "\" ";
	else
		check = "\' ";
	i = 0;
	while (str[i])
	{
		if (ft_is_this((char *)check, str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
