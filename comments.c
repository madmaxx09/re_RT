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