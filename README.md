Quick explanation of the .rt file formating


some comments
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


//la fonction qui envera les rayons sera recursive 
//je dois choisir la depth de cette recursion 
//et choisir le nombres de rayons que j'envoie par zone de mon champ de vision
//pour calculer l'ombre je dois trouver l'angle entre la normale de ma surface et mon rayon entrant
//je peux "peut etre facilement" ajouter une notion de texture en ayant un indice de reflection en fct de celle ci
//dans la fonction recursive le nouveau point de depart du rayon sera son point d'arrivé précedent si celui ci est pertinent
//je pourrais definir des zones dans lesquelles envoyer les rayons si prob de performance
//sur un seul thread zzz

void	get_viewport(t_data *data)
{
	t_vec u;
	//double focus_dist = 10;
	double theta = deg_to_rad(data->cam.fov);
	double h = tan(theta / 2);
	double view_high = 2 * h; //final formula should be 2 * h * focus_dist (focus_dist = 10)
	double view_wide = view_high * (WIDTH / HEIGHT);

	// u v w unit vectors 
	t_vec w = norm_vec(data->cam.dir);  //is the unit vector of lookfrom - lookat so it should just be our cam.dir
	if (fabs(w.x) < EPSILON && fabs(w.z) < EPSILON)
		u = (t_vec){1, 0, 0}; // Set u to {1, 0, 0} for the special case
	else
		u = norm_vec(vec_cross((t_vec){0, 1, 0}, w));
	t_vec v = vec_cross(w, u);

	//vectors following the viewport edges

	t_vec   viewport_u = mult_vec(u, view_wide); 
	t_vec   viewport_v = mult_vec(mult_vec(v, -1.0), view_high);

	//size between each horizontal and vertical pixel in the frame

	data->view.x_pix = div_vec(viewport_u, (double)WIDTH);
	data->view.y_pix = div_vec(viewport_v, (double)HEIGHT);

	//getting the upper left pixel of the frame
	t_vec   tmp = div_vec(viewport_v, 2);
	t_vec   tmp2 = div_vec(viewport_u, 2);
	t_vec   tmp3 = dif_vec(data->cam.pos, w);
	tmp3 = dif_vec(tmp3, tmp2);
	tmp3 = dif_vec(tmp3, tmp);
	t_vec   up_left = tmp3; //origin - w - viewport_u/2 - viewport_v/2;

	tmp = add_vec(data->view.x_pix, data->view.y_pix);
	tmp = mult_vec(tmp, 0.5);
	data->view.pix00 = add_vec(up_left, tmp);
	data->view.pos = data->cam.pos;
}

#include "./includes/miniRT.h"

void print_args(t_data *data)
{
	// printf("Ambient Light:\n");
	// printf("\tRatio: %f\n", data->amli.ratio);
	// printf("\tColor: R: %f, G: %f, B: %f\n", data->amli.color.r, data->amli.color.g, data->amli.color.b);

	// printf("Camera:\n");
	// printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->cam.pos.x, data->cam.pos.y, data->cam.pos.z);
	// printf("\tVector: X: %f, Y: %f, Z: %f\n", data->cam.dir.x, data->cam.dir.y, data->cam.dir.z);
	// printf("\tFOV: %d\n", data->cam.fov);

	// printf("Light:\n");
	// printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->light.pos.x, data->light.pos.y, data->light.pos.z);
	// printf("\tLighting: %f\n", data->light.ratio);

	printf("Spheres:\n");
	while(data->sphere)
	{
		printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->sphere->pos.x, data->sphere->pos.y, data->sphere->pos.z);
		printf("\tDiameter: %f\n", data->sphere->diam);
		printf("\tColor: R: %f, G: %f, B: %f\n", data->sphere->rgb.r, data->sphere->rgb.g, data->sphere->rgb.b);
		printf ("\tMat : %f\n", data->sphere->mat);
		data->sphere = data->sphere->next;
	}

	printf("Viewport:\n");
	// printf("\tHorizontal Vector: X: %f, Y: %f, Z: %f\n", data->view.hori.x, data->view.hori.y, data->view.hori.z);
	// printf("\tVertical Vector: X: %f, Y: %f, Z: %f\n", data->view.verti.x, data->view.verti.y, data->view.verti.z);
	printf("\tX Pixel Vector: X: %f, Y: %f, Z: %f\n", data->view.x_pix.x, data->view.x_pix.y, data->view.x_pix.z);
	printf("\tY Pixel Vector: X: %f, Y: %f, Z: %f\n", data->view.y_pix.x, data->view.y_pix.y, data->view.y_pix.z);
	printf("\tPixel 00: X: %f, Y: %f, Z: %f\n", data->view.pix00.x, data->view.pix00.y, data->view.pix00.z);

	printf("Plans:\n");
	printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->plan->pos.x, data->plan->pos.y, data->plan->pos.z);
	printf("\tVector: X: %f, Y: %f, Z: %f\n", data->plan->dir.x, data->plan->dir.y, data->plan->dir.z);
	printf("\tColor: R: %f, G: %f, B: %f\n", data->plan->rgb.r, data->plan->rgb.g, data->plan->rgb.b);
}