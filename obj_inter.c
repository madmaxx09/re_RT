#include "./includes/miniRT.h"

//-b +- racine de b2 - 4ac sur 2a
//rayon touche surface si il est solution de lequation de la sphere
t_vec  normal_cyl(t_cyl *cyl, t_vec point)
{
    t_vec normal;
    double h;

    h = dot_prod(dif_vec(point, cyl->pos), cyl->dir);
    normal = norm_vec(dif_vec(point, add_vec(cyl->pos, mult_vec(cyl->dir, h))));
    return (normal);
}

double hit_sp(t_vec ori, t_vec direction, t_sphere *sphere)
{
    t_vec ro_c =  dif_vec(ori, sphere->pos); //origine rayon vs centre sphere
    double a;
    double half_b;
    double c;
    double discri;

    a = dot_prod(direction, direction);
    half_b = dot_prod(ro_c, direction);
    c = dot_prod(ro_c, ro_c) - ((sphere->diam / 2) * (sphere->diam / 2));
    discri = (half_b * half_b) - (a * c);
    if (discri < 0)
        return (-1.0);
    else
        return(-half_b - sqrt(discri)) / a; //jai inverse potentiellement une valeur ici
}

double hit_pl(t_vec ori, t_vec dir, t_plan *plan)
{
    double t;
    double deno;

    deno = dot_prod(dir, plan->dir);
    if (fabs(deno) > 1e-6)
    {
        t = ((dot_prod(plan->dir, plan->pos) - dot_prod(ori, plan->dir)) / deno);
        if (t >= 0)
            return (t);
    }
    return (-1.0);
}

static void intersect_tube_quadratic(t_cyl *cyl, t_vec ori, t_vec dir, double abc[3])
{
    t_vec   ray_inter_tube;
    t_vec   dif_dir;

    ray_inter_tube = vec_cross(dir, cyl->dir);
    abc[0] = dot_prod(ray_inter_tube, ray_inter_tube);
    dif_dir = vec_cross(dif_vec(ori, cyl->pos), cyl->dir);
    abc[1] = 2.0 * dot_prod(ray_inter_tube, dif_dir);
    abc[2] = dot_prod(dif_dir, dif_dir) - ((cyl->diam / 2) * (cyl->diam / 2));
}

double  hit_cyl(t_vec ori, t_vec dir, t_cyl *cyl, double t_max)
{
    double abc[3];
    double d;
    double h;
    double t;

    intersect_tube_quadratic(cyl, ori, dir, abc);
    d = (abc[1] * abc[1]) - (4.0 * abc[0] * abc[2]);
    if (d < 0 || abc[0] < 1e-6)
        return (-1.0);
    d = sqrt(d);
    t = (-abc[1] - d) / (2.0 * abc[0]);
    h = dot_prod(dif_vec(lin_comb(1.0, ori, t, dir), cyl->pos), cyl->dir);
    if (t < 0.001 || t > t_max || fabs(h) > cyl->height / 2.0)
    {
        t = (-abc[1] + d) / (2.0 * abc[0]);
        h = dot_prod(dif_vec(lin_comb(1.0, ori, t, dir), cyl->pos), cyl->dir);
        if (t < 0.001 || t > t_max || fabs(h) > cyl->height / 2.0)
            return (-1.0);
    }
    return (t);
}

double hit_disc(t_vec ori, t_vec dir, t_disc *disc, double t_max)
{
    double deno;
    double t;

    deno = dot_prod(disc->dir, dir);
    if (fabs(deno) > 1e-6)
    {
        t = dot_prod(dif_vec(disc->pos, ori), disc->dir) / deno;
        if (t > 0.001 && t < t_max && dist(disc->pos, lin_comb(1.0, ori, t, dir)) <= (disc->diam / 2))
            return (t);
    }
    return (-1.0);
}