/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:45:51 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/23 13:02:32 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c_s;
	int				i;

	i = 0;
	c_s = (unsigned char *)s;
	while (i < (int)n)
	{
		if (c_s[i] == (unsigned char)c)
			return (c_s + i);
		i++;
	}
	return (NULL);
}
