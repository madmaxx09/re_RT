#include "./includes/miniRT.h"

inline double length_squared(t_vec vec)
{
    return ((double)(vec.x * vec.x + vec.y * vec.y + vec.z *vec.z));
}

//random double between [0, 1]
double  random_double(void)
{
    return (rand() / (RAND_MAX + 1.0));
}

//random double between [min, max]
double rand_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

inline t_vec    random_vec(double min, double max)
{
    return ((t_vec){rand_range(min, max), rand_range(min, max), rand_range(min, max)});
}

inline t_vec    random_vec_in_unit_sphere(void)
{
    t_vec   p;
    while (1)
    {
        p = random_vec(-1, 1);
        //print_vec(p);
        if (length_squared(p) < 1)
            return (p);
    }
}

inline t_vec   random_unit_vec(void)
{
    return (norm_vec(random_vec_in_unit_sphere()));
}