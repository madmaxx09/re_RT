/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   rgb_math.c										 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:47:18 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:20 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline t_rgb	color_blend(double t, t_rgb a, t_rgb b)
{
	if (is_black(a) && is_black(b))
		return ((t_rgb){0, 0, 0});
	return ((t_rgb){
		(1.0 - t) * a.r + (t * b.r),
		(1.0 - t) * a.g + (t * b.g),
		(1.0 - t) * a.b + (t * b.b)
	});
}

inline double	gamma_cor(double color)
{
	if (color > 0)
		return (sqrt(color));
	return (0);
}

inline double	clamp(double color, double min, double max)
{
	if (color < min)
		return (min);
	if (color > max)
		return (max);
	return (color);
}

inline int	rgb_to_color(t_rgb rgb)
{
	int	color;

	color = 0;
	if (rgb.r != rgb.r)
		rgb.r = 0;
	if (rgb.g != rgb.g)
		rgb.g = 0;
	if (rgb.b != rgb.b)
		rgb.b = 0;
	rgb.r = gamma_cor(clamp(rgb.r, 0.0, 0.999)) * 256;
	rgb.g = gamma_cor(clamp(rgb.g, 0.0, 0.999)) * 256;
	rgb.b = gamma_cor(clamp(rgb.b, 0.0, 0.999)) * 256;
	color |= ((int)rgb.r & 0xFF) << 16;
	color |= ((int)rgb.g & 0xFF) << 8;
	color |= ((int)rgb.b & 0xFF);
	return (color);
}

inline double	color_scaling(t_hit hit, t_vec dir)
{
	double	cos;

	cos = dot_prod(hit.normal, dir);
	return (cos);
}
