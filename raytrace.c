/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   raytrace.c										 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:47:10 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:13 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline t_vec	pxss(t_vec xp, t_vec yp)
{
	double	x;
	double	y;

	x = -0.5 + random_double();
	y = -0.5 + random_double();
	return (add_vec(mult_vec(xp, x), mult_vec(yp, y)));
}

inline t_rgb	color_ray(t_data *data, int i, int j, t_rgb *blend)
{
	return (add_rgbs(*blend, div_rgb(ray(data->view.pos, dif_vec(
						add_vec(add_vec(add_vec(mult_vec(
										data->view.xp, i), mult_vec
									(data->view.yp, j)),
								data->view.pix00), pxss
							(data->view.xp, data->view.yp)),
						data->view.pos), MAX_DEPTH, data), SAMPLE)));
}

void	raytrace(t_data *data)
{
	t_rgb		blend;
	int			i;
	int			j;
	int			sample;

	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			blend = (t_rgb){0, 0, 0};
			sample = -1;
			while (++sample < SAMPLE)
			{
				blend = color_ray(data, i, j, &blend);
			}
			data->image[j * WIDTH + i] = blend;
		}
	}
}

t_rgb	ray(t_vec origine, t_vec direction, int depth, t_data *data)
{
	t_hit	hit;
	t_rgb	blend;
	double	pdf;

	blend = (t_rgb){0, 0, 0};
	if (depth <= 0)
		return ((t_rgb){0, 0, 0});
	hit = hit_box(origine, direction, data);
	if (hit.hitted == false)
		return (color_blend(0.5 * (direction.y + 1.0),
				data->back_2, data->back_1));
	if (hit.hitted == true && hit.mat == 3)
		return (hit.obj_color);
	pdf = scatter_pdf(&hit);
	blend = mult_rgb(ray(hit.point,
				hit.new_dir, depth - 1, data), hit.obj_color);
	if (depth == MAX_DEPTH)
		return (add_rgbs(blend, data->amli.color));
	return (blend);
}

//lambertian is 2 
//anything between 0 and 1 is metal with the 
//amount between 0 and 1 being the fuzziness of this metal (0 not fuzzy at all)
//si je veux renvoyer + de rayon vers la lum c'est ici
t_vec	get_new_dir(t_hit *hit)
{
	t_vec	dir;

	if (hit->mat != 2.0)
	{
		return (add_vec(reflect(hit->ray_in, hit->normal),
				mult_vec(random_unit_vec(), (hit->mat))));
	}
	dir = add_vec(hit->normal, random_unit_vec());
	if (near_zero(dir))
		dir = hit->normal;
	return (dir);
}
