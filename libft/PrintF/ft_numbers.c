/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:16:06 by mdor              #+#    #+#             */
/*   Updated: 2023/04/24 18:33:02 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putint(int n)
{
	int		i;
	char	*str;

	str = ft_itoa(n);
	i = ft_putstr(str);
	free(str);
	return (i);
}

int	ft_putpourcent(void)
{
	ft_putchr('%');
	return (1);
}

int	ft_count(unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

int	ft_put_unsigned_int(unsigned int n)
{
	int	count;

	if (n >= 10)
	{
		ft_put_unsigned_int (n / 10);
		ft_put_unsigned_int (n % 10);
	}
	else
	{
		ft_putchr((n + '0'));
	}
	count = ft_count(n);
	return (count);
}
