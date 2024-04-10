#include "./miniRT.h"

typedef struct s_malloc		t_malloc;

typedef enum
{
	CYL, 
	PLN,
	SPH
}	obj_type;

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
	double x;
	double y;
	double z;
}	t_vec;

typedef struct s_ray
{
    t_vec ori;
    t_vec dir;
}   t_ray;

typedef struct s_cyl
{
	t_vec	pos;
	t_vec	dir;
	double	diam;
	double	height;
	t_rgb	rgb;
	struct s_cyl	*next;
}	t_cyl;

typedef struct s_plan
{
	t_vec	pos;
	t_vec	dir;
	t_rgb	rgb;
	struct s_plan	*next;
}	t_plan;

typedef struct s_sphere
{
	t_vec	pos;
	double	diam;
	t_rgb	rgb;
	int		mat;
	struct s_sphere *next;
}	t_sphere; 

typedef	struct s_cam
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
	int 	init;
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

typedef struct	s_hit
{
	t_vec	ray_in;
	int		mat;
	t_vec	normal;
	t_vec	point;
	bool	hitted;
	t_rgb	obj_color;
	double	root;
}	t_hit;

typedef struct s_data
{
	t_amli		amli;
	t_cam		cam;
	t_sphere	*sphere;
	t_plan		*plan;
	t_cyl		*cyl;
	t_light		light;
	t_viewport	view;
	//t_obj		*obj;
	void		*mlx;
	void		*wind;
	t_malloc	*head;
	int			error_trigger;
}	t_data;