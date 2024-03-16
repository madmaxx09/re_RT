/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:53:05 by mdor              #+#    #+#             */
/*   Updated: 2023/04/24 18:34:26 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_manage(char prefix, va_list arguments)
{
	int	count;

	count = 0;
	if (prefix == 's')
		count = ft_putstr(va_arg(arguments, char *));
	else if (prefix == 'd' || prefix == 'i')
		count = ft_putint(va_arg(arguments, int));
	else if (prefix == 'u')
		count = ft_put_unsigned_int(va_arg(arguments, unsigned int));
	else if (prefix == 'p')
		count = ft_putptr(va_arg(arguments, unsigned long long int));
	else if (prefix == '%')
		count = ft_putpourcent();
	else if (prefix == 'c')
		count = ft_putchr(va_arg(arguments, int));
	else if (prefix == 'x' || prefix == 'X')
		count = ft_puthexa(va_arg(arguments, unsigned int), prefix);
	return (count);
}

int	ft_prefixcheck(char c)
{
	if (c == 's' || c == 'd' || c == 'i' || c == 'u' || c == 'p'
		|| c == '%' || c == 'c' || c == 'x' || c == 'X')
		return (1);
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		written_chars;
	va_list	arguments;

	written_chars = 0;
	i = 0;
	va_start(arguments, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			if (ft_prefixcheck(str[i + 1]))
				written_chars += ft_manage(str[i + 1], arguments);
			else if (str[i + 1])
				written_chars += ft_putchr(str[i + 1]);
			i++;
		}
		else if (str[i] != '%')
			written_chars += ft_putchr(str[i]);
		i++;
	}
	va_end(arguments);
	return (written_chars);
}
