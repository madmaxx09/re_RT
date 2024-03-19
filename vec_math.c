#include "./includes/miniRT.h"

inline double  len_vec(t_vec vec)
{
    return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z *vec.z));
}

t_vec   dif_vec(t_vec a, t_vec b)
{
    return ((t_vec){a.x - b.x, a.y - b.y, a.z - c.z}); 
}

double   dist(t_vec  src, t_vec dest)
{
    //distance = difference entre 2 vec puis longueur de celui ci etant la racine de produit le signe
    //na pas de valeur 
    return (len_vec(dif_vec(src, dest)));
}

t_vec   norm_vec(t_vec vec)
{
    double  i;

    i = (1.0 / len_vec(vec));
    return ((t_vec){vec.x * i, vec.y * i, vec.z * i});
}