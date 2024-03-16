/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:13:17 by mdor              #+#    #+#             */
/*   Updated: 2024/03/15 11:06:08 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *stock, char *buff)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!stock)
		return (ft_strdu(buff));
	new = malloc((ft_strle(stock) + ft_strle(buff) + 1) * sizeof(char));
	if (!new)
		return ((protect(stock, NULL)));
	if (stock)
		while (stock[++i] != '\0')
			new[i] = stock[i];
	while (buff[j] != '\0')
		new[i++] = buff[j++];
	new[ft_strle(stock) + ft_strle(buff)] = '\0';
	free(stock);
	return (new);
}

char	*ft_read(int fd, char *stock)
{
	int		readcheck;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return ((protect(stock, NULL)));
	readcheck = 1;
	while (!ft_strchr_gnl(stock, '\n') && readcheck != 0)
	{
		readcheck = read(fd, buff, BUFFER_SIZE);
		if (readcheck == -1)
			return (protect(stock, buff));
		if (readcheck == 0)
			break ;
		buff[readcheck] = '\0';
		stock = ft_strjoin_gnl(stock, buff);
		if (stock == NULL)
			break ;
	}
	free(buff);
	return (stock);
}

char	*ft_getline(char *stock)
{
	char	*line;
	int		i;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (++i != -1 && stock[i] && stock[i] != '\n')
		line[i] = stock[i];
	if (stock[i] == '\n')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_clean(char *stock, char *line)
{
	char	*cleaned;
	int		i;
	int		j;

	i = 0;
	if (line == NULL)
		return (protect(stock, NULL));
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	cleaned = (char *)malloc((ft_strle(stock) - i + 1) * sizeof(char));
	if (!cleaned)
		return (protect(stock, NULL));
	i++;
	j = 0;
	while (stock[i])
		cleaned[j++] = stock[i++];
	cleaned[j] = '\0';
	free(stock);
	return (cleaned);
}

char	*get_next_line(int fd)
{
	static char	*stock[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	stock[fd] = ft_read(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	line = ft_getline(stock[fd]);
	stock[fd] = ft_clean(stock[fd], line);
	return (line);
}
