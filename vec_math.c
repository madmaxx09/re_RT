#include "./includes/miniRT.h"

//vecteur normal = perpendiculaire a ma surface a un point donné
//on fait un vec normal dirigé vers l'ext donc pt - pos
t_vec   normal_su(t_sphere *sph, t_vec point)
{
    return (norm_vec(dif_vec(point, sph->pos)));
}

inline double  len_vec(t_vec vec)
{
    return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z *vec.z));
}

inline t_vec	vec_by_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x * b.x, a.y * b.y, a.z * b.z});
}

inline t_vec   dif_vec(t_vec a, t_vec b)
{
    return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z}); 
}

inline t_vec    div_vec(t_vec a, double b)
{
    return ((t_vec){a.x / b, a.y / b, a.z / b});
}

inline t_vec    mult_vec(t_vec a, double b)
{
    return ((t_vec){a.x * b, a.y * b, a.z * b});
}

inline t_vec    add_vec(t_vec a, t_vec b)
{
    return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

//distance = difference entre 2 vec puis longueur de celui ci etant la racine de produit le signe
//na pas de valeur 
double   dist(t_vec  src, t_vec dest)
{
    return (len_vec(dif_vec(src, dest)));
}

t_vec   norm_vec(t_vec vec)
{
    double  i;
    if (len_vec(vec) == 0)
    {
        return ((t_vec){0,0,0});    
    }
    i = (1.0 / len_vec(vec));
    return ((t_vec){vec.x * i, vec.y * i, vec.z * i});
}

inline double dot_prod(t_vec a, t_vec b)
{
    return ((double)a.x * b.x + a.y * b.y + a.z * b.z);
}

void    print_vec(t_vec a)
{
    printf("x : %f\n", a.x);
    printf("y : %f\n", a.y);
    printf("z : %f\n", a.z);
}