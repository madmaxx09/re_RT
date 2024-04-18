/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   random.c										   :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:46:54 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:02 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

//random double between [0, 1]
inline double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

//random double between [min, max]
inline double	rand_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

inline t_vec	random_vec(double min, double max)
{
	return ((t_vec){rand_range(min, max),
		rand_range(min, max), rand_range(min, max)});
}

//changer la distrib pour envoyer vers la lumiere
inline t_vec	random_vec_in_unit_sphere(void)
{
	t_vec	p;

	while (1)
	{
		p = random_vec(-1, 1);
		if (length_squared(p) < 1)
			return (p);
	}
}

inline t_vec	random_unit_vec(void)
{
	return (norm_vec(random_vec_in_unit_sphere()));
}
