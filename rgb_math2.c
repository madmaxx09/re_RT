/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:09:34 by mdor              #+#    #+#             */
/*   Updated: 2024/04/18 15:09:35 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	print_rgb(t_rgb rgb)
{
	printf("r : %f\ng : %f\nb : %f\n", rgb.r, rgb.g, rgb.b);
}

inline t_rgb	div_rgb(t_rgb rgb, double a)
{
	return ((t_rgb){rgb.r / a, rgb.g / a, rgb.b / a});
}

inline t_rgb	mult_rgb_dub(t_rgb rgb, double a)
{
	return ((t_rgb){rgb.r * a, rgb.g * a, rgb.b * a});
}

inline t_rgb	mult_rgb(t_rgb a, t_rgb b)
{
	return ((t_rgb){a.r * b.r, a.g * b.g, a.b * b.b});
}

inline t_rgb	add_rgbs(t_rgb a, t_rgb b)
{
	return ((t_rgb){a.r + b.r, a.g + b.g, a.b + b.b});
}
