/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:51:19 by mdor              #+#    #+#             */
/*   Updated: 2022/12/14 21:17:47 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		i;
	char		ch;

	ch = c;
	str = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
