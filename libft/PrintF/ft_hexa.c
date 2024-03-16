/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:52:45 by mdor              #+#    #+#             */
/*   Updated: 2023/04/25 15:27:00 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_hex(unsigned int n, char type)
{
	if (n >= 16)
	{
		ft_puthexa((n / 16), type);
		ft_puthexa((n % 16), type);
	}
	else
	{
		if (n < 10)
			ft_putchr(n + '0');
		else if (type == 'x')
			ft_putchr(n - 10 + 'a');
		else if (type == 'X')
			ft_putchr(n - 10 + 'A');
	}
}

int	ft_puthexa(unsigned int n, char type)
{
	int	count;

	ft_hex(n, type);
	count = hexlen(n);
	return (count);
}
