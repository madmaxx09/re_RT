/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additionnalfcts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:28:40 by mdor              #+#    #+#             */
/*   Updated: 2023/04/24 18:33:58 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printptr(unsigned long long int ptr)
{
	if (ptr >= 16)
	{
		ft_printptr(ptr / 16);
		ft_printptr(ptr % 16);
	}
	else
	{
		if (ptr < 10)
			ft_putchr(ptr + '0');
		else
			ft_putchr(ptr - 10 + 'a');
	}
}

int	ft_putptr(unsigned long long int ptr)
{
	int	count;

	count = 0;
	count = write(1, "0x", 2);
	ft_printptr(ptr);
	count += hexlen(ptr);
	return (count);
}

int	ft_length(long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len++;
		return (len);
	}
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_do(char *new, int len, long nbr, int neg)
{
	new[len] = '\0';
	if (neg == 0)
		nbr = -nbr;
	while (--len >= 0)
	{
		new[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (neg == 0)
		new[0] = '-';
	return (new);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		len;
	int		neg;
	long	nbr;

	nbr = n;
	neg = 1;
	if (n < 0)
		neg = 0;
	len = ft_length(nbr);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new = ft_do(new, len, nbr, neg);
	return (new);
}
