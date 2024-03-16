/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:52:59 by mdor              #+#    #+#             */
/*   Updated: 2022/12/14 21:43:36 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	b;
	size_t	i;

	a = 0;
	b = 0;
	i = 0;
	while (dst[a] != '\0' && a < dstsize)
		a++;
	i = i + a;
	while (src[b])
		b++;
	i = i + b;
	if (a == dstsize)
		return (i);
	b = 0;
	while (src[b] && a + b < dstsize - 1)
	{
		dst[a + b] = src[b];
		b++;
	}
	dst[a + b] = '\0';
	return (i);
}
