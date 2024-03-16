/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:29:29 by mdor              #+#    #+#             */
/*   Updated: 2022/12/14 17:15:05 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	inset(char c, char const *set)
{
	int	k;

	k = 0;
	while (set[k])
	{
		if (set[k] == c)
			return (1);
		k++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		debut;
	int		fin;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	debut = 0;
	fin = ft_strlen(s1);
	while (inset(s1[debut], set) == 1)
		debut++;
	if (debut == fin)
	{
		trimmed = ft_strdup("");
		if (!trimmed)
			return (NULL);
		else
			return (trimmed);
	}
	while (inset(s1[fin - 1], set) == 1 && (fin > debut))
		fin--;
	trimmed = ft_substr(s1, debut, fin - debut);
	return (trimmed);
}
