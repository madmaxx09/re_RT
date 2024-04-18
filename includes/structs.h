/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:49 by mdor              #+#    #+#             */
/*   Updated: 2024/04/18 14:05:51 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

typedef struct s_malloc		t_malloc;

typedef enum s_obj_type
{
	CYL,
	PLN,
	SPH,
	DSC
}	t_obj_type;

typedef struct s_malloc
{
	void		*adress;
	t_malloc	*next;
}	t_malloc;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	ori;
	t_vec	dir;
}	t_ray;

typedef struct s_disc
{
	t_vec			dir;
	t_vec			pos;
	double			diam;
	double			mat;
	struct s_disc	*next;
	t_rgb			rgb;
}	t_disc;

typedef struct s_cyl
{
	t_vec			pos;
	t_vec			dir;
	double			diam;
	double			height;
	double			mat;
	t_rgb			rgb;
	struct s_cyl	*next;
}	t_cyl;

typedef struct s_plan
{
	t_vec			pos;
	t_vec			dir;
	t_rgb			rgb;
	double			mat;
	struct s_plan	*next;
}	t_plan;

typedef struct s_sphere
{
	t_vec			pos;
	double			diam;
	t_rgb			rgb;
	double			mat;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cam
{
	t_vec	pos;
	t_vec	dir;
	int		fov;
	int		init;
}	t_cam;

typedef struct s_amli
{
	int		init;
	t_rgb	color;
	double	ratio;
}	t_amli;

typedef struct s_light
{
	t_vec	pos;
	double	ratio;
	int		init;
	t_rgb	rgb;
}	t_light;

typedef struct s_viewport
{
	t_vec	pos;
	t_vec	hori;
	t_vec	verti;
	t_vec	x_pix;
	t_vec	y_pix;
	t_vec	pix00;

}	t_viewport;

typedef struct s_hit
{
	t_vec		ray_in;
	t_vec		new_dir;
	double		mat;
	t_obj_type	type;
	double		diam;
	t_vec		normal;
	t_vec		cyl_dir;
	t_vec		point;
	bool		hitted;
	t_rgb		obj_color;
	double		root;
}	t_hit;

typedef struct s_data
{
	t_amli		amli;
	t_cam		cam;
	t_sphere	*sphere;
	t_plan		*plan;
	t_cyl		*cyl;
	t_disc		*disc;
	t_light		light;
	t_viewport	view;
	t_rgb		back_1;
	t_rgb		back_2;
	int			back_set;
	void		*mlx;
	void		*wind;
	t_malloc	*head;
	t_rgb		*image;
	int			error_trigger;
}	t_data;
