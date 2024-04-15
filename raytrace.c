#include "./includes/miniRT.h"

//la fonction qui envera les rayons sera recursive 
//je dois choisir la depth de cette recursion 
//et choisir le nombres de rayons que j'envoie par zone de mon champ de vision


//pour calculer l'ombre je dois trouver l'angle entre la normale de ma surface et mon rayon entrant
//je peux "peut etre facilement ajouter une notion de texture en ayant un indice de reflection en fct de celle ci"


//dans la fonction recursive le nouveau point de depart du rayon sera son point d'arrivé précedent si celui ci est pertinent
//je pourrais definir des zones dans lesquelles envoyer les rayons si prob de performance
//sur un seul thread zzz


t_vec	px_sample_square(t_vec x_pix, t_vec y_pix)
{
	double x;
	double y;

	x = -0.5 + random_double();
	y = -0.5 + random_double();
	return (add_vec(mult_vec(x_pix, x), mult_vec(y_pix, y)));
}

void    raytrace(t_data *data)
{
    get_viewport(data);
    t_viewport view;
    t_rgb color;
    t_rgb blend;

    view = data->view;
    for (int j = 0; j <= HEIGHT; ++j)
    {
        for (int i = 0; i <= WIDTH; ++i)
        {
            blend = (t_rgb){0,0,0};
			for (int sample = 0; sample < SAMPLES; sample++)
			{
				t_vec   px_cent = add_vec(add_vec(mult_vec(view.x_pix, (double)i), mult_vec(view.y_pix, (double)j)), view.pix00);
				px_cent = add_vec(px_cent, px_sample_square(view.x_pix, view.y_pix));
				color = ray_shot(view.pos, dif_vec(px_cent, view.pos), MAX_DEPTH, data);
                blend = add_rgbs(blend, div_rgb(color, SAMPLES));
			}
            mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(blend));
        }
    }
    
}

t_hit  hit_box(t_vec ori, t_vec dir, t_data *data)
{
    t_hit   hit;
    t_data  tmp;
    double  t;
    double  ret_val;

    hit.hitted = false;
    ret_val = MAXFLOAT;
    tmp = *data;
    while (tmp.sphere != NULL)
    {
        if (tmp.sphere != NULL)
        {
            t = hit_sp(ori, dir, tmp.sphere);
            if (t > 0.001 && t < ret_val)//moyen de rendre le code plus efficace ici en calculant uniquement pour le dernier hit juste trouver un moyen de garder le bon objet 
            {
                hit.hitted = true;
                ret_val = t;
                hit.point = (t_vec){ori.x + dir.x * t, ori.y + dir.y * t, ori.z + dir.z * t};
                hit.normal = normal_sp(tmp.sphere, hit.point);
                hit.mat = tmp.sphere->mat;
                hit.ray_in = dir;
                hit.obj_color = tmp.sphere->rgb;
            }
            tmp.sphere = tmp.sphere->next;
        }
    }
    while (tmp.plan != NULL)
    {
        if (tmp.plan != NULL)
        {
            t = hit_pl(ori, dir, tmp.plan);
            if (t > 0.001 && t < ret_val)
            {
                hit.hitted = true;
                ret_val = t;
                hit.point = (t_vec){ori.x + dir.x * t, ori.y + dir.y * t, ori.z + dir.z * t};
                hit.normal = norm_vec(tmp.plan->dir);
                hit.ray_in = dir;
                hit.obj_color = tmp.plan->rgb;
                hit.mat = tmp.plan->mat;
            }
            tmp.plan = tmp.plan->next;
        }
    }
    while (tmp.cyl != NULL)
    {
        if (tmp.cyl != NULL)
        {
            t = hit_cyl(ori, dir, tmp.cyl, ret_val);
            if (t > 0.001 && t < ret_val)
            {
                hit.hitted = true;
                ret_val = t;
                hit.point = (t_vec){ori.x + dir.x * t, ori.y + dir.y * t, ori.z + dir.z * t};
                hit.normal = normal_cyl(tmp.cyl, hit.point);
                hit.ray_in = dir;
                hit.obj_color = tmp.cyl->rgb;
                hit.mat = 0;
            }
            tmp.cyl = tmp.cyl->next;
        }
    }
    while (tmp.disc != NULL)
    {
        if (tmp.disc != NULL)
        {
            t = hit_disc(ori, dir, tmp.disc, ret_val);
            if (t > 0.001 && t < ret_val)
            {
                hit.hitted = true;
                ret_val = t;
                hit.point = (t_vec){ori.x + dir.x * t, ori.y + dir.y * t, ori.z + dir.z * t};
                hit.normal = tmp.disc->dir;
                hit.ray_in = dir;
                hit.obj_color = tmp.disc->rgb;
                hit.mat = 0;
            }
            tmp.disc = tmp.disc->next;
        }
    }
    hit.root = ret_val;
    return (hit);
}


// //chaque rebond s'add au precedent mais de moins en moins fort
// //pour l'instant on dirait que je n'ai pas besoin de data ici je pourrais potentiellement le remplacer par t_hit prev hit et si besoin je calle les deux vecs dans hit 
// t_rgb ray_shot(t_vec origine, t_vec direction, int depth, t_data *data) 
// {
//     t_hit   hit;
//     t_rgb   blend;
//    //t_rgb   attenuation;
//     double  blender;
    
//     blender = 0;
//     blend = (t_rgb){0,0,0};
    
//     //derniere recursion aucune lumiere ajoutée
//     if (depth <= 0)
//         return ((t_rgb){0,0,0});
//     //check si hit
//     hit = hit_box(origine, direction, data);
//     //si hit alors je renvoie la couleur de l'objet
// 	if (hit.hitted == true)
//     {
//         // if (hit.mat == 1)
//         //     return (ray_shot(hit.point, get_new_dir(hit, &blender), depth - 1, data));
//         // else
//             //attenuation = hit.obj_color; 
//             return mult_rgb(ray_shot(hit.point, get_new_dir(hit, &blender), depth - 1, data), hit.obj_color);
//             //return mult_rgb_dub(ray_shot(hit.point, get_new_dir(hit, &blender), depth - 1, data), 0.5);
//     }
        
//     // blend = ray_shot(hit.point, get_new_dir(hit, &blender), depth - 1, data);
//     // blend = mult_rgb_dub(blend, blender);
//     // blend = mult_rgb(blend, hit.obj_color);
//     // if (depth == MAX_DEPTH)
//     //     return (add_rgbs(blend, data->amli.color));
//     double t = 0.5*(direction.y + 1.0);
//     return (add_rgbs(mult_rgb_dub((t_rgb){1,1,1}, (1.0 - t)), mult_rgb_dub((t_rgb){0.5,0.7,1}, (t))));
//     //return (blend);
//     //return (data->amli.color);
// }

t_rgb ray_shot(t_vec origine, t_vec direction, int depth, t_data *data) 
{
    t_hit   hit;
    t_rgb   blend;
    blend = (t_rgb){0,0,0};
    if (depth <= 0)
        return ((t_rgb){0,0,0});
    hit = hit_box(origine, direction, data);
    if (hit.hitted == false) // choisir si on met un background ou bien seulement amli
    {
        //return (data->amli.color);
        double t = 0.5*(direction.y + 1.0);
        return (add_rgbs(mult_rgb_dub((t_rgb){1,1,1}, (1.0 - t)), mult_rgb_dub((t_rgb){0.5,0.7,1}, (t))));
    }
    if (hit.hitted == true && hit.mat == 3)
    {
        return (hit.obj_color);
        //print_rgb(blend);
    }
    double pdf = scatter_pdf(&hit);
    (void)pdf;
    blend = mult_rgb(ray_shot(hit.point, hit.new_dir, depth - 1, data), hit.obj_color);
    if (depth == MAX_DEPTH)
        return (add_rgbs(blend, data->amli.color));

    return (blend);
}

double color_scaling(t_hit hit, t_vec dir)
{
    double cos;

    cos = dot_prod(hit.normal, dir);
    return (cos);
}

t_vec	get_new_dir(t_hit *hit)
{
	t_vec dir;
    
	//je peux rajouter des composants différents pour complexifier 
	//lambertian is 2 
	//anything between 0 and 1 is metal with the amount between 0 and 1 being the fuzziness of this metal (0 not fuzzy at all)
    if (hit->mat != 2)//if material is not 2 then it is metal and the mat number is the fuzzines of the reflection on this metal
    {
        return (add_vec(reflect(hit->ray_in, hit->normal), mult_vec(random_unit_vec(), (hit->mat))));
    }
    dir = add_vec(hit->normal, random_unit_vec());
    if (near_zero(dir))
        dir = hit->normal;
	return (dir);
}