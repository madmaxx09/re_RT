#include "./includes/miniRT.h"

//la fonction qui envera les rayons sera recursive 
//je dois choisir la depth de cette recursion 
//et choisir le nombres de rayons que j'envoie par zone de mon champ de vision


//pour calculer l'ombre je dois trouver l'angle entre la normale de ma surface et mon rayon entrant
//je peux "peut etre facilement ajouter une notion de texture en ayant un indice de reflection en fct de celle ci"


//dans la fonction recursive le nouveau point de depart du rayon sera son point d'arrivé précedent si celui ci est pertinent
//je pourrais definir des zones dans lesquelles envoyer les rayons si prob de performance
//sur un seul thread zzz




void    raytrace(t_data *data)
{
    get_viewport(data);
    t_viewport view = data->view;
    int color;
    for (int j = 0; j <= HEIGHT; ++j)
    {
        for (int i = 0; i <= WIDTH; ++i)
        {
            t_vec   px_cent = add_vec(add_vec(mult_vec(view.x_pix, (double)i), mult_vec(view.y_pix, (double)j)), view.pix00);
            color = ray_shot(view.pos, dif_vec(px_cent, view.pos), 0, data);
            mlx_pixel_put(data->mlx, data->wind, i, j, color);
            if (i == 0 && j == 0)
            {
                printf("ori \n");
                print_vec(view.pos);
                printf("dir  \n");
                print_vec(px_cent);
            }
        }
    }
    
}


//-b +- racine de b2 - 4ac sur 2a
//rayon touche surface si il est solution de lequation de la sphere
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

// int    ray_shot(t_vec origine, t_vec direction, int depth, t_data *data)//int for test but void
// {
//     //var qui renveront le prochain ray ou qui seront necessaire a l'affichage
//     // t_vec   new_ori;
//     // t_vec   new_dir;
//     (void)depth;
//     (void)data;
//     t_rgb white = {255, 255, 255};
//     t_rgb blue  = {127, 178, 255};
//     t_rgb red   = {255, 0, 0};
//     //ici premier test d'afficher un truc 
//     t_vec norm = norm_vec(direction);
//     double t = 0.5*( norm.y + 1.0 );
//     //printf("%f\n", t);
//     t_rgb rgb = add_rgbs(mult_rgb_dub(white, (1.0 - t)), mult_rgb_dub(blue, (t)));
    
//     double discri;
    
//     // if (direction.x < 0.5)
//     // {
//     //     printf("dir : ");
//     //     print_vec(direction);
//     // }
//     //on va bouger nos objects hits de ici pca avant on va les packe en un volume comprenant tout les objets, si le rayon ne touche pas
//     //ce volume on ne prendra pas la peine d'aller plus loin, le rayon ne touchera aucun objet 

//     // if (hit_bvh(origine, direction, data) == 1)
//     // {

//     // }
//     discri = hit_sp(origine, direction, data->sphere);
//     if (discri > 0) // ici on va chercher a shade la couleur de l'bjet en fct de l'angle du rayon par rapport a la surface 
//     {//besoin de faire une ombre en proportion de langle entre vec origine et rayon normal 
//         //donc je cherche le dot product du vecteur normal et de mon rayon 
//         //OMBRE EN FCT DE SRC LUM ET NON DE CAM
//         t_vec point = {origine.x + direction.x * discri, origine.y + direction.y * discri, origine.z + direction.z * discri};
//         t_vec normal_sp = normal_su(data->sphere, point);
//         double dot = dot_prod(norm_vec(direction), normal_sp);
//         //t_rgb shade =  {normal_sp.x * red.r, normal_sp.y * red.g, normal_sp.z * red.b};
//         t_rgb shade = mult_rgb_dub(red, dot);
//         shade = mult_rgb_dub(shade, data->amli.ratio);
//         //valeur positive = point ext de la sphere jai l'impression
//         //chercher le vec normal
//         //t_vec normal = normal_su(data->sphere, )
//         return (rgb_to_color(shade));
//     }
//     rgb = mult_rgb_dub(rgb, data->amli.ratio);
//     return (rgb_to_color(rgb));
//     //je dois aussi avoir un cas ou je recurse pas et je put rien pour un pixel x si je n'ai rien hit au premier shoot
//     //avoir un cas ou le hit ne compte pas si il est trop proche ou trop loin

//     // if (depth == 3) //definir la pronfondeur
//     //     custom_pixel_put(new_ori, ) //trouver comment compute le x et y de mon pixel
//     // else
//     //     ray_shot(new_ori, new_dir, depth + 1, data);
// }

t_hit  hit_box(t_vec ori, t_vec dir, t_data *data, int depth)
{
    t_hit   hit;
    t_data  tmp;
    double  t;
    double  ret_val;
    (void)depth;                 //ici probablement faire varier la distance de hit minimum pour que le hit compte en fonction du rebond/surface de celui ci

    hit.hitted = false;
    ret_val = INFINITY;
    tmp = *data;
    while (tmp.sphere != NULL)
    {
        if (tmp.sphere != NULL)
        {
            // printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->sphere->pos.x, data->sphere->pos.y, data->sphere->pos.z);
            // printf("\tDiameter: %f\n", data->sphere->diam);
            // printf("\tColor: R: %f, G: %f, B: %f\n", data->sphere->rgb.r, data->sphere->rgb.g, data->sphere->rgb.b);
            t = hit_sp(ori, dir, tmp.sphere);
            if (t > 0.0 && t < ret_val)
            {
                // printf("helo\n");
                hit.hitted = true;
                ret_val = t;
                hit.obj_color = tmp.sphere->rgb;
                hit.point = (t_vec){{ori.x + dir.x * t, ori.y + dir.y * t, ori.z + dir.z * t}}
                hit.normal = normal_su(tmp.sphere, );
            }
            tmp.sphere = tmp.sphere->next;
        }
    }
    hit.root = ret_val;
    return (hit);
}

//pour l'instant on dirait que je n'ai pas besoin de data ici je pourrais potentiellement le remplacer par t_hit prev hit et si besoin je calle les deux vecs dans hit 
int ray_shot(t_vec origine, t_vec direction, int depth, t_data *data) 
{
    // t_vec   new_ori;
    // t_vec   new_dir;
    t_hit   hit;
    (void)depth;

    
    hit = hit_box(origine, direction, data, depth); //je veux l'endroit ou mon ray a touché
    if (hit.hitted == false)
        return (rgb_to_color((t_rgb){0, 255, 0}));
    else if (depth == MAX_DEPTH)
    {
        return (rgb_to_color(hit.obj_color)); //ici je devrai / j'aurai déjà du proceder au différents shading de l'objet
    }
	else
		ray_shot(hit.point, get_new_dir(hit), depth + 1, data);  //a priori ici que je reCURSE ma fonction si trop lent considerer un autre moyen 
}

t_vec	get_new_dir(t_hit) //prototype ici on cherche à renvoyer en fonction de la surface 
{
	/*trouver un moyen de dire via la struct hit que je dois renvoyer un ou plusieurs rayons en fonction*/
}