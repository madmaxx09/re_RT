#include "./includes/miniRT.h"


	//double focal = 1.0 / (2 * tan(deg_to_rad(data->cam.fov) / 2)); //focal taking fov into acc



void    get_viewport(t_data *data)
{
    double focus_dist = 10;
    double theta = deg_to_rad(data->cam.fov);
    double h = tan(theta / 2);
    double view_high = 2 * h * focus_dist; //final formula should be 2 * h * focus_dist (focus_dist = 10)
    double view_wide = view_high * (WIDTH / HEIGHT);

    // u v w unit vectors 
    t_vec w = norm_vec(data->cam.dir);  //is the unit vector of lookfrom - lookat so it should just be our cam.dir
    t_vec u = norm_vec(vec_cross((t_vec){0, 1, 0}, w));
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
    t_vec   up_left = tmp3;

    tmp = add_vec(data->view.x_pix, data->view.y_pix);
    tmp = mult_vec(tmp, 0.5);
    data->view.pix00 = add_vec(up_left, tmp);
    data->view.pos = data->cam.pos;
    //data->view.pix00 = (t_vec){-10.1, 10.1, -1};

}