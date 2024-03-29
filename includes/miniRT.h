#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include "structs.h"
# include "mymath.h"
# define ASPECT_RATIO (16.0/9.0)
# define WIDTH 1200
# define HEIGHT (WIDTH / ASPECT_RATIO)
# define MAX_DEPTH 3
# define SAMPLES 4
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 666
# endif

void	ft_error_exit(char *str, t_data *data);
void		*gc_malloc(size_t required_memory, t_data *data);
int    ray_shot(t_vec origine, t_vec direction, int depth, t_data *data);
void    get_viewport(t_data *data);
//Parsing functions

int	ft_atob(const char *str, int b_p, int a_p, double *res);
void	parse_rt(char *rt_file, t_data *data);
void print_args(t_data *data);
void    manage_rgb(char **tab, t_rgb *store, t_data *data, int pos);
void manage_vectors(char **tab, t_vec *store ,t_data *data, int pos);
void free_tabl(char **tab);
void manage_ambiant(char **tab, t_data *data);
void manage_cam(char **tab, t_data *data);
void manage_light(char **tab, t_data *data);
void manage_sphere(char **tab, t_data *data);
void manage_plan(char **tab, t_data *data);
void    manage_cyl(char **tab, t_data *data);

//mlx hooks
int presskey(int key, t_data *data);
void    raytrace(t_data *data);


# endif