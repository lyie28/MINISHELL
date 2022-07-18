/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:34:13 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/09/07 16:48:05 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_whitespace(char test)
{
	if ((test > 8 && test < 14) || test == 32)
		return (0);
	return (1);
}

static int	ft_checksize(int result, int i, char *str)
{
	unsigned long int	test;

	test = result;
	if ((test * 10 + (str[i] - '0') > LONG_MAX))
		return (1);
	return (0);
}

static int	ft_ret_val(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_whitespace(str[i]) == 0)
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	if (str[i] < 48 || str[i] > 57)
		return (0);
	result = str[i] - '0';
	i++;
	while (str[i] > 47 && str[i] < 58)
	{
		if (ft_checksize(result, i, (char *)str))
			return (ft_ret_val(sign));
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
