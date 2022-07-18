/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:47:09 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/09/01 16:38:08 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_move(char *dest, char *src, size_t i)
{
	char	tmp;

	tmp = src[i];
	dest[i] = tmp;
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*c_dst;
	char	*c_src;

	i = 0;
	c_dst = dst;
	c_src = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			ft_move(c_dst, c_src, i);
			i--;
		}
		return (dst);
	}
	while (i < len)
	{
		ft_move(c_dst, c_src, i);
		i++;
	}
	return (dst);
}
