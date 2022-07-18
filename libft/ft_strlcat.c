/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:48:35 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/24 10:34:01 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size_src;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	size_src = 0;
	if (!dst && !src)
		return (0);
	while (src[size_src])
		size_src++;
	if (dstsize == 0)
		return (size_src);
	while (dst[i])
		i++;
	while (src[j] && i + j < dstsize - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (j < dstsize)
		dst[i + j] = '\0';
	if (dstsize < i)
		return (size_src + dstsize);
	return (i + size_src);
}
