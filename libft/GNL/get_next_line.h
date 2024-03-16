/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:21:42 by mdor              #+#    #+#             */
/*   Updated: 2023/03/13 23:42:12 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 666
# endif

size_t		ft_strle(const char *str);
char		*ft_strjoin_gnl(char *stock, char *buff);
char		*ft_strchr_gnl(char *s, int c);
char		*get_next_line(int fd);
void		*protect(char *fdp, char *sonpote);
char		*ft_strdu(const char *s1);

#endif 
