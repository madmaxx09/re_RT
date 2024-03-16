/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:19:38 by mdor              #+#    #+#             */
/*   Updated: 2022/12/15 15:10:14 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wrdcount(char const *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (count);
}

char	*ft_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_free(char **tabl, int i)
{
	int	j;

	j = 0;
	if (tabl)
	{
		while (j < i)
		{
			free(tabl[j]);
			j++;
		}
		free(tabl);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		iter;
	char	**tabl;
	size_t	i;
	size_t	j;

	iter = -1;
	i = -1;
	j = 0;
	tabl = malloc((ft_wrdcount(s, c) + 1) * sizeof(char *));
	if (!tabl || !s)
		return (ft_free(tabl, j));
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && iter < 0)
			iter = i;
		else if ((s[i] == c || i == ft_strlen(s)) && iter >= 0)
		{
			tabl[j] = ft_dup(s, iter, i);
			if (tabl[j++] == NULL)
				return (ft_free(tabl, j));
			iter = -1;
		}
	}
	tabl[j] = 0;
	return (tabl);
}
