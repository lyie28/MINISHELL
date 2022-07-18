/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:04:52 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/09/01 16:38:28 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u_nbr;

	u_nbr = n;
	if (fd < 0)
		return ;
	if (n < 0)
	{
		u_nbr = -n;
		ft_putchar_fd('-', fd);
	}
	if (u_nbr > 9)
	{
		ft_putnbr_fd(u_nbr / 10, fd);
		ft_putnbr_fd(u_nbr % 10, fd);
	}
	else
		ft_putchar_fd(u_nbr + '0', fd);
}
