#include "./includes/miniRT.h"

inline t_vec    vec_cross(t_vec a, t_vec b)
{
    t_vec c;

    c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

    return (c);
}

inline double deg_to_rad(int to_convert)
{
    return ((double)(to_convert * 3.14159) / 180);
}