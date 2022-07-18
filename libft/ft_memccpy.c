/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:45:38 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/24 10:29:01 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;
	size_t			i;

	i = 0;
	c_dst = dst;
	c_src = (unsigned char *)src;
	while (i < n && (unsigned char)c != c_src[i])
	{
		c_dst[i] = c_src[i];
		i++;
	}
	if (i == n)
		return (NULL);
	c_dst[i] = c_src[i];
	i++;
	return (dst + i);
}
