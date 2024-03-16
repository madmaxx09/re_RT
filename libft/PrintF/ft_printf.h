/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <mdor@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:01:44 by mdor              #+#    #+#             */
/*   Updated: 2023/04/25 13:32:15 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int		ft_putstr(char *str);
int		ft_putchr(char c);
int		ft_putint(int n);
int		ft_putpourcent(void);
int		ft_manage(char prefix, va_list arguments);
int		ft_printf(const char *str, ...);
int		ft_prefixcheck(char c);
char	*ft_itoa(int n);
int		ft_put_unsigned_int(unsigned int n);
int		ft_putptr(unsigned long long int ptr);
int		hexlen(unsigned long long int n);
int		ft_puthexa(unsigned int n, char type);

#endif
