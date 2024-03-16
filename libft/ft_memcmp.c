/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:51:22 by mdor              #+#    #+#             */
/*   Updated: 2022/12/14 21:20:04 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;
	size_t				i;

	i = -1;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (++i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
	}
	return (0);
}
