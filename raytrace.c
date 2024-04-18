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

inline t_vec	px_sample_square(t_vec x_pix, t_vec y_pix)
{
	double	x;
	double	y;

	x = -0.5 + random_double();
	y = -0.5 + random_double();
	return (add_vec(mult_vec(x_pix, x), mult_vec(y_pix, y)));
}

void	raytrace(t_data *data)
{
	t_viewport	view;
	t_rgb		blend;
	int			i;
	int			j;
	int			sample;

	get_viewport(data);
	view = data->view;
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			blend = (t_rgb){0, 0, 0};
			sample = -1;
			while (++sample < SAMPLES)
			{
				blend = add_rgbs(blend, div_rgb(ray_shot(view.pos, dif_vec(add_vec(add_vec(add_vec(mult_vec(view.x_pix, (double)i), mult_vec(view.y_pix, (double)j)), view.pix00), px_sample_square(view.x_pix, view.y_pix)), view.pos), MAX_DEPTH, data), SAMPLES));
			}
			data->image[j * WIDTH + i] = blend;
		}
	}
}

t_rgb	ray_shot(t_vec origine, t_vec direction, int depth, t_data *data)
{
	t_hit	hit;
	t_rgb	blend;
	double	pdf;

	blend = (t_rgb){0, 0, 0};
	if (depth <= 0)
		return ((t_rgb){0, 0, 0});
	hit = hit_box(origine, direction, data);
	if (hit.hitted == false)
	{
		if (data->back_set == 1)
			return (color_blend(0.5 * (direction.y + 1.0), data->back_2, data->back_1));
		else
			return ((t_rgb){0, 0, 0});
	}
	if (hit.hitted == true && hit.mat == 3)
		return (hit.obj_color);
	pdf = scatter_pdf(&hit);
	blend = mult_rgb(ray_shot(hit.point, hit.new_dir, depth - 1, data), hit.obj_color);
	if (depth == MAX_DEPTH)
	{
		if (is_black(blend))
			return ((t_rgb){0, 0, 0});
		return (add_rgbs(blend, data->amli.color));
	}
	return (blend);
}

double	color_scaling(t_hit hit, t_vec dir)
{
	double	cos;

	cos = dot_prod(hit.normal, dir);
	return (cos);
}

//lambertian is 2 
//anything between 0 and 1 is metal with the amount between 0 and 1 being the fuzziness of this metal (0 not fuzzy at all)
//si je veux renvoyer + de rayon vers la lum c'est ici
t_vec	get_new_dir(t_hit *hit)
{
	t_vec	dir;

	if (hit->mat != 2)
	{
		return (add_vec(reflect(hit->ray_in, hit->normal),
				mult_vec(random_unit_vec(), (hit->mat))));
	}
	dir = add_vec(hit->normal, random_unit_vec());
	if (near_zero(dir))
		dir = hit->normal;
	return (dir);
}
