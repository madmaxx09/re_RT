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
# include "structs.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 666
# endif


void	ft_error_exit(char *str, t_data *data);
//Parsing functions

int	ft_atob(const char *str, int b_p, int a_p, double *res);
void	parse_rt(char *rt_file, t_data *data);
void print_args(t_data *data);
void    manage_rgb(char **tab, t_rgb *store, t_data *data, int pos);
void manage_vectors(char **tab, t_vec *store ,t_data *data, int pos);


# endif