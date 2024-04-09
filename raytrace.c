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
    t_viewport view = data->view;
    t_rgb color;
    t_rgb blend;
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
                // printf("sample : %d\n", sample);
                // print_rgb(blend);
			}
            mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(blend));
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

t_rgb new_color(t_hit hit, t_sphere sphere, t_vec dir)
{
    t_rgb color;
    double angle;

    angle = dot_prod(hit.normal, dir);

    color = hit.obj_color;
    color = add_rgbs(color, mult_rgb_dub(sphere.rgb, -angle));
    return (color);
}

t_hit  hit_box(t_vec ori, t_vec dir, t_data *data, int depth)
{
    t_hit   hit;
    t_data  tmp;
    double  t;
    double  ret_val;
    (void)depth;                 //ici probablement faire varier la distance de hit minimum pour que le hit compte en fonction du rebond/surface de celui ci

	// if (depth == MAX_DEPTH)
	// 	return (hit);
    hit.hitted = false;
    ret_val = INFINITY;
    tmp = *data;
    while (tmp.sphere != NULL)
    {
        if (tmp.sphere != NULL)
        {
            t = hit_sp(ori, dir, tmp.sphere);
            if (t > 0.0 && t < ret_val)
            {
                hit.hitted = true;
                ret_val = t;
                hit.point = (t_vec){ori.x + dir.x * t, ori.y + dir.y * t, ori.z + dir.z * t};;
                hit.normal = normal_su(tmp.sphere, hit.point);
                //hit.obj_color = new_color(hit, *tmp.sphere, dir);
                hit.obj_color = tmp.sphere->rgb; //en fonction de la profondeur, du matériel, et de l'orientation on recalculera la lumière du point à chaque fois
            }
            tmp.sphere = tmp.sphere->next;
        }
    }
    hit.root = ret_val;
    return (hit);
}


//chaque rebond s'add au precedent mais de moins en moins fort
//pour l'instant on dirait que je n'ai pas besoin de data ici je pourrais potentiellement le remplacer par t_hit prev hit et si besoin je calle les deux vecs dans hit 
t_rgb ray_shot(t_vec origine, t_vec direction, int depth, t_data *data) 
{
    t_hit   hit;
    t_rgb   blend;
    
    blend = (t_rgb){0,255,0};
    if (depth == 0)
    {
        //printf("test\n");
        return ((t_rgb){0,0,0}); //ici il faudrait aussi prendre en compte la profondeur, car un troisième rebond qui ne touche pas doit qd même me renvoyer une couleur 
    }
    hit = hit_box(origine, direction, data, depth); //je veux l'endroit ou mon ray a touché
	if (hit.hitted == true)
    {
        return mult_rgb_dub(ray_shot(hit.point, get_new_dir(hit), depth -1, data), 0.5);
        //return mult_rgb(hit.obj_color, ray_shot(hit.point, get_new_dir(hit), depth - 1, data));
		//return (mult_rgb(mult_rgb_dub(ray_shot(hit.point, get_new_dir(hit), depth - 1, data), MAX_DEPTH - depth/ MAX_DEPTH), hit.obj_color));  
    }
    //printf("test\n");
    return (blend); //ici on return 
}

t_vec	get_new_dir(t_hit hit)
{
	t_vec dir;

    dir = add_vec(hit.normal, random_unit_vec());
    print_vec(dir);
	return (dir);
}