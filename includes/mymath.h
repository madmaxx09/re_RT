#ifndef MYMATH_H
# define MYMATH_H

//vector math 

double   dist(t_vec src, t_vec dest);
t_vec   normal_su(t_sphere *sph, t_vec point);
double  len_vec(t_vec vec);
t_vec   dif_vec(t_vec a, t_vec b);
t_vec   norm_vec(t_vec vec);
t_vec    div_vec(t_vec a, double b);
t_vec    mult_vec(t_vec a, double b);
t_vec    add_vec(t_vec a, t_vec b);
double  dot_prod(t_vec a, t_vec b);

//color math
int rgb_to_color(t_rgb rgb);
t_rgb    mult_rgb_dub(t_rgb rgb, double a);
t_rgb    add_rgbs(t_rgb a, t_rgb b);


#endif