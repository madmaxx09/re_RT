#ifndef OBJECTS_H
# define OBJECTS_H
# include "./miniRT.h"

# define DIFFUSE 0
# define SPECULAR 1



typedef t_vec   (*t_f_normal)(t_list *obj, t_hit *hit);
typedef t_vec   (*t_f_inter)(t_list *obj, t_ray *ray, double t_min, double t_max);

typedef struct s_obj //un pointeur vers l'elem un pointeur vers le node suivant peut etre limite faire un array de pointeurs pour vitesse ? 
{
    t_f_normal  normal;
    t_f_inter   point;
    union
    {
        t_plan      pln;
        t_sphere    sph;
        t_cyl       cyl;
    };
}	t_obj;


#endif