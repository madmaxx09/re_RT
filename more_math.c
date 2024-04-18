/* ************************************************************************** */
/*																		   	  */
/*														:::	  ::::::::        */
/*   more_math.c										:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:46:24 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:46:26 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

inline double	deg_to_rad(int to_convert)
{
	return ((double)(to_convert * PI) / 180);
}

inline t_vec	reflect(t_vec v, t_vec n)
{
	t_vec	temp;
	double	tmp;

	tmp = 2 * dot_prod(v, n);
	temp = mult_vec(n, tmp);
	return (dif_vec(v, temp));
}

inline bool	near_zero(t_vec test)
{
	double	s;

	s = 1e-8;
	return ((fabs(test.x) < s) && (fabs(test.y) < s) && (fabs(test.z) < s));
}
