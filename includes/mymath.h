#ifndef MYMATH_H
# define MYMATH_H

double  random_double(void);
double length_squared(t_vec vec);
t_vec    random_vec(double min, double max);

//vector math 

double   dist(t_vec src, t_vec dest);
t_vec   normal_su(t_sphere *sph, t_vec point);
double  len_vec(t_vec vec);
t_vec   dif_vec(t_vec a, t_vec b);
t_vec   norm_vec(t_vec vec);
t_vec    div_vec(t_vec a, double b);
t_vec    mult_vec(t_vec a, double b);
t_vec    add_vec(t_vec a, t_vec b);
t_vec    vec_cross(t_vec a, t_vec b);
double  dot_prod(t_vec a, t_vec b);
double deg_to_rad(int to_convert);
t_vec	vec_by_vec(t_vec a, t_vec b);
void    print_vec(t_vec a);
t_vec    random_unit_vec(void);
t_vec    reflect(t_vec v, t_vec n);
t_vec    random_vec_in_unit_sphere(void);

//color math
int rgb_to_color(t_rgb rgb);
t_rgb    mult_rgb_dub(t_rgb rgb, double a);
t_rgb    add_rgbs(t_rgb a, t_rgb b);
t_rgb mult_rgb(t_rgb a, t_rgb b);
t_rgb    div_rgb(t_rgb rgb, double a);
void    print_rgb(t_rgb rgb);


#endif