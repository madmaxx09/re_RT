#include "./includes/miniRT.h"

inline t_vec    rand_cosine_dir()
{
    double r1;
    double r2;
    double phi;

    r1 = random_double();
    r2 = random_double();
    phi = 2 * PI * r1;
    return ((t_vec){cos(phi) * sqrt(r2), 
            sin(phi) * sqrt(r2), 
            sqrt(1 - r2)});
}

double  scatter_pdf(t_hit *hit)
{
    double cos_theta;

    cos_theta = dot_prod(hit->normal, hit->new_dir);
    hit->new_dir = get_new_dir(hit);
    if (cos_theta < 0)
        return (0);
    else
        return (cos_theta / PI);
}