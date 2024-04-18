/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   viewport.c										 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:48:05 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:48:06 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	get_viewport(t_data *data)
{
	t_vec	u;
	t_vec	w;
	t_vec	v;

	w = norm_vec(data->cam.dir);
	if (fabs(w.x) < EPSILON && fabs(w.z) < EPSILON)
		u = (t_vec){1, 0, 0};
	else
		u = norm_vec(vec_cross((t_vec){0, 1, 0}, w));
	v = vec_cross(w, u);
	data->view.xp = div_vec(mult_vec(u, 2 * (tan
					(deg_to_rad(data->cam.fov) / 2))
				* (WIDTH / HEIGHT)), (double)WIDTH);
	data->view.yp = div_vec(mult_vec(mult_vec(v, -1.0),
				2 * (tan(deg_to_rad(data->cam.fov) / 2))), (double)HEIGHT);
	data->view.pix00 = add_vec(dif_vec(dif_vec(dif_vec(data->cam.pos, w),
					div_vec(mult_vec(u, 2 * (tan(deg_to_rad(data->cam.fov) / 2))
							* (WIDTH / HEIGHT)), 2)), div_vec(mult_vec
					(mult_vec(v, -1.0), 2 * (tan(deg_to_rad
								(data->cam.fov) / 2))), 2)),
			mult_vec(add_vec(data->view.xp, data->view.yp), 0.5));
	data->view.pos = data->cam.pos;
}
