/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:43:31 by mdor              #+#    #+#             */
/*   Updated: 2024/04/18 14:43:35 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

inline t_vec	get_obj_normal(t_hit *hit)
{
	if (hit->type == SPH)
		return (normal_sp(hit->normal, hit->diam, hit->point));
	else if (hit->type == PLN)
		return (norm_vec(hit->normal));
	else if (hit->type == CYL)
		return (normal_cyl(hit->normal, hit->cyl_dir, hit->point));
	return (hit->normal);
}

inline t_vec	normal_cyl(t_vec pos, t_vec dir, t_vec point)
{
	t_vec	normal;
	double	h;

	h = dot_prod(dif_vec(point, pos), dir);
	normal = norm_vec(dif_vec(point, add_vec(pos, mult_vec(dir, h))));
	return (normal);
}
