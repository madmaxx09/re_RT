/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:06:20 by mdor              #+#    #+#             */
/*   Updated: 2024/04/18 15:06:21 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline double	length_squared(t_vec vec)
{
	return ((double)(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

//vecteur normal = perpendiculaire a ma surface a un point donné
//on fait un vec normal dirigé vers l'ext donc pt - pos
inline t_vec	normal_sp(t_vec pos, double diam, t_vec point)
{
	return (div_vec(dif_vec(point, pos), diam / 2));
}

inline double	len_vec(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

inline t_vec	vec_by_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x * b.x, a.y * b.y, a.z * b.z});
}

inline t_vec	dif_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}
