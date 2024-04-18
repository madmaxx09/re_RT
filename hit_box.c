/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   hit_box.c										  :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 20:11:00 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 20:11:02 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline void	sphere_check(t_sphere *sp, t_hit *hit, t_vec ori, t_vec dir)
{
	double	t;

	while (sp != NULL)
	{
		t = hit_sp(ori, dir, sp);
		if (t > 0.001 && t < hit->root)
		{
			hit->hitted = true;
			hit->root = t;
			hit->normal = sp->pos;
			hit->diam = sp->diam;
			hit->type = SPH;
			hit->obj_color = sp->rgb;
			hit->mat = sp->mat;
		}
		sp = sp->next;
	}
}

inline void	plane_check(t_plan *pl, t_hit *hit, t_vec ori, t_vec dir)
{
	double	t;

	while (pl != NULL)
	{
		t = hit_pl(ori, dir, pl);
		if (t > 0.001 && t < hit->root)
		{
			hit->hitted = true;
			hit->root = t;
			hit->type = PLN;
			hit->normal = pl->dir;
			hit->obj_color = pl->rgb;
			hit->mat = pl->mat;
		}
		pl = pl->next;
	}
}

inline void	cyl_check(t_cyl *cyl, t_hit *hit, t_vec ori, t_vec dir)
{
	double	t;

	while (cyl != NULL)
	{
		t = hit_cyl(ori, dir, cyl, hit->root);
		if (t > 0.001 && t < hit->root)
		{
			hit->hitted = true;
			hit->root = t;
			hit->type = CYL;
			hit->normal = cyl->pos;
			hit->cyl_dir = cyl->dir;
			hit->diam = cyl->diam;
			hit->mat = cyl->mat;
			hit->obj_color = cyl->rgb;
		}
		cyl = cyl->next;
	}
}

inline void	disc_check(t_disc *disc, t_hit *hit, t_vec ori, t_vec dir)
{
	double	t;

	while (disc != NULL)
	{
		t = hit_disc(ori, dir, disc, hit->root);
		if (t > 0.001 && t < hit->root)
		{
			hit->hitted = true;
			hit->root = t;
			hit->type = DSC;
			hit->normal = disc->dir;
			hit->obj_color = disc->rgb;
			hit->mat = disc->mat;
		}
		disc = disc->next;
	}
}

inline t_hit	hit_box(t_vec ori, t_vec dir, t_data *data)
{
	t_hit	hit;
	t_data	tmp;

	hit.type = -1;
	hit.hitted = false;
	hit.root = MAXFLOAT;
	tmp = *data;
	sphere_check(data->sphere, &hit, ori, dir);
	plane_check(data->plan, &hit, ori, dir);
	cyl_check(data->cyl, &hit, ori, dir);
	disc_check(data->disc, &hit, ori, dir);
	hit.point = (t_vec){ori.x + dir.x * hit.root,
		ori.y + dir.y * hit.root, ori.z + dir.z * hit.root};
	hit.ray_in = dir;
	hit.normal = get_obj_normal(&hit);
	return (hit);
}
