#include "./includes/miniRT.h"

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

bool near_zero(t_vec test)
{
    double s;

    s = 1e-8;
    return ((fabs(test.x) < s) && (fabs(test.y) < s) && (fabs(test.z) < s));
}