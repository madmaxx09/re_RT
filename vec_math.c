/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   vec_math.c										 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:47:54 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:56 by mdor			 ###   ########.fr	      */
/*																		      */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline double	dot_prod(t_vec a, t_vec b)
{
	return ((double)a.x * b.x + a.y * b.y + a.z * b.z);
}

void	print_vec(t_vec a)
{
	ft_printf("x : %f\n", a.x);
	ft_printf("y : %f\n", a.y);
	ft_printf("z : %f\n", a.z);
}

inline t_vec	lin_comb(double a, t_vec i, double b, t_vec j)
{
	return (add_vec(mult_vec(i, a), mult_vec(j, b)));
}
