/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:09:26 by mdor              #+#    #+#             */
/*   Updated: 2024/04/18 15:09:28 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline t_vec	div_vec(t_vec a, double b)
{
	return ((t_vec){a.x / b, a.y / b, a.z / b});
}

inline t_vec	mult_vec(t_vec a, double b)
{
	return ((t_vec){a.x * b, a.y * b, a.z * b});
}

inline t_vec	add_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

//distance = difference entre 2 vec puis 
//longueur de celui ci etant la racine de produit le signe
//na pas de valeur 
inline double	dist(t_vec src, t_vec dest)
{
	return (len_vec(dif_vec(src, dest)));
}

inline t_vec	norm_vec(t_vec vec)
{
	double	len;

	len = len_vec(vec);
	if (len == 0)
	{
		return ((t_vec){0, 0, 0});
	}
	return ((t_vec){vec.x / len, vec.y / len, vec.z / len});
}
