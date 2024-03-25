#include "./includes/miniRT.h"

void    raytrace(t_data *data)
{
    int color;
    t_vec   origin = {0,0,0};
    t_vec   focal = {0,0,1};
    t_vec   verti = {0, 2.0, 0};
    t_vec   hori = {(2.0 * ASPECT_RATIO), 0, 0};
    t_vec   tmp;

    tmp = dif_vec(origin, div_vec(hori, 2));
    tmp = dif_vec(tmp, div_vec(verti, 2));
    t_vec   low_left = dif_vec(tmp, focal);

    for (int j = 0; j <= HEIGHT - 1; j++)
    {
        for (int i = 0; i <= WIDTH; i++)
        {
            double u = (double)i / (WIDTH - 1);
            double v = (double)j / (HEIGHT - 1);
            color = ray_shot(origin, dif_vec(add_vec(low_left, add_vec(mult_vec(hori, u), mult_vec(verti, v))), origin), 0, data);
            mlx_pixel_put(data->mlx, data->wind, i, j, color);
        }
    }
}
//-b +- racine de b2 - 4ac sur 2a
//rayon touche surface si il est solution de lequation de la sphere
double hit_sp(t_vec ori, t_vec direction, t_data *data)
{
    t_vec ro_c =  dif_vec(ori, data->sphere->pos); //origine rayon vs centre sphere
    
    double a;
    double half_b;
    double c;
    double discri;

    a = dot_prod(direction, direction);
    half_b = dot_prod(ro_c, direction);
    c = dot_prod(ro_c, ro_c) - ((data->sphere->diam / 2) * (data->sphere->diam / 2));
    //printf("%f | %f\n", data->sphere->diam, c);
    discri = (half_b * half_b) - (a * c);
    if (discri < 0)
        return (-1.0);
    else
    {
        return (-half_b + sqrt(discri)) / a; //jai inverse potentiellement une valeur ici
    }
}

int    ray_shot(t_vec origine, t_vec direction, int profondeur, t_data *data)//int for test but void
{
    //var qui renveront le prochain ray ou qui seront necessaire a l'affichage
    // t_vec   new_ori;
    // t_vec   new_dir;
    (void)profondeur;
    (void)data;
    t_rgb white = {255, 255, 255};
    t_rgb blue  = {127, 178, 255};
    t_rgb red   = {255, 0, 0};
    //ici premier test d'afficher un truc 
    t_vec norm = norm_vec(direction);
    double t = 0.5*( norm.y + 1.0 );
    t_rgb rgb = add_rgbs(mult_rgb_dub(white, (1.0 - t)), mult_rgb_dub(blue, (t)));

    double discri;

    discri = hit_sp(origine, direction, data);
    if (discri > 0) // ici on va chercher a shade la couleur de l'bjet en fct de l'angle du rayon par rapport a la surface 
    {//besoin de faire une ombre en proportion de langle entre vec origine et rayon normal 
        //donc je cherche le dot product du vecteur normal et de mon rayon 
        t_vec point = {origine.x + direction.x * discri, origine.y + direction.y * discri, origine.z + direction.z * discri};
        t_vec normal_sp = normal_su(data->sphere, point);
        double dot = dot_prod(norm_vec(direction), normal_sp);
        //t_rgb shade =  {normal_sp.x * red.r, normal_sp.y * red.g, normal_sp.z * red.b};
        t_rgb shade = mult_rgb_dub(red, dot);
        shade = mult_rgb_dub(shade, data->amli.ratio);
        //valeur positive = point ext de la sphere jai l'impression
        //chercher le vec normal
        //t_vec normal = normal_su(data->sphere, )
        return (rgb_to_color(shade));
    }
    rgb = mult_rgb_dub(rgb, data->amli.ratio);
    return (rgb_to_color(rgb));







    //je dois aussi avoir un cas ou je recurse pas et je put rien pour un pixel x si je n'ai rien hit au premier shoot
    //avoir un cas ou le hit ne compte pas si il est trop proche ou trop loin

    // if (profondeur == 3) //definir la pronfondeur
    //     custom_pixel_put(new_ori, ) //trouver comment compute le x et y de mon pixel
    // else
    //     ray_shot(new_ori, new_dir, profondeur + 1, data);
}