#include "./includes/miniRT.h"

double  random_double(void)
{
    return (rand() / (RAND_MAX + 1.0));
}

inline t_vec    vec_cross(t_vec a, t_vec b)
{
    t_vec c;

    c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

    // printf("%f\n", c.x);
    // printf("%f\n", c.y);
    // printf("%f\n", c.z);
    return (c);
}

inline double deg_to_rad(int to_convert)
{
    return ((double)(to_convert * 3.14159) / 180);
}

inline t_vec    reflect(t_vec v, t_vec n)
{
    t_vec temp;
    double tmp;

    tmp = 2 * dot_prod(v, n);
    temp = mult_vec(n, tmp);
    return (dif_vec(v, temp));
}

inline t_vec    random_unit_vec(void)
{
    return (norm_vec((t_vec){random_double(), random_double(), random_double()}));
	//changer ça pour que mon vec puisse renvoyer du négatif aussi 
}