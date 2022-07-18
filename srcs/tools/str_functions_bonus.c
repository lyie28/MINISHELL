/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:42:26 by user42            #+#    #+#             */
/*   Updated: 2021/09/09 13:55:01 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	int		size;
	int		i;
	int		j;

	if ((!(s1)) || (!(s2)))
		return (NULL);
	i = -1;
	j = -1;
	size = (ft_strlen((char *)s1)) + (ft_strlen((char *)s2));
	cat = malloc(sizeof(char) * size + 1);
	if (!cat)
		return (NULL);
	while (s1[++i])
		cat[i] = s1[i];
	while (s2[++j])
		cat[i + j] = s2[j];
	cat[i + j] = '\0';
	return (cat);
}
