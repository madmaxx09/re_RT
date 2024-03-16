#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
//# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 666
# endif

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

typedef struct s_cyl
{
	t_vec	pos;
	t_vec	dir;
	double	rad;
	double	height;
	s_cyl	*next;
}	t_cyl;

typedef struct s_plan
{
	t_vec	pos;
	t_vec	dir;
	s_plan	*next;
}	t_plan;

typedef struct s_sphere
{
	t_vec	pos;
	t_vec	dir;
	double	rad;
	s_sphere *next;
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

typedef struct s_data
{
	t_amli		amli;
	t_cam		cam;
	t_sphere	*sphere;
	t_plan		*plan;
	t_cyl		*cyl;
	void		*mlx;
	void		*wind;
	t_malloc	*head;
	int			error_trigger;
}	t_data;


# endif