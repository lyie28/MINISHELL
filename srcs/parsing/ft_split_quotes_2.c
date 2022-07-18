/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:35:56 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 16:40:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_dollar_check_split(char *str, int *i, int new_i)
{
	*i = new_i;
	if (ft_strcmp(str, "$") == 0)
	{
		free(str);
		str = ft_strdup(" $");
		return (str);
	}
	return (str);
}
