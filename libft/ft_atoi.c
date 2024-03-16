/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:05:14 by mdor              #+#    #+#             */
/*   Updated: 2022/12/15 13:22:55 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	famoso;
	int			neg;
	long int	prot;

	famoso = 0;
	neg = 1;
	prot = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		neg *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		famoso = famoso * 10 + (*str - 48);
		if (neg == -1 && prot > famoso)
			return (0);
		if (neg == 1 && prot > famoso)
			return (-1);
		prot = famoso;
		str++;
	}
	return (famoso * neg);
}
