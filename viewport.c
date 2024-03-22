#include "./includes/miniRT.h"

void    get_viewport(t_data *data)
{
	double focal = 1.0 / (2 * tan(deg_to_rad(data->cam.fov) / 2)); //focal taking fov into acc

	double v_high = 2.0 * focal; 
	double v_wide = v_high * ASPECT_RATIO;
	t_vec	w = data->cam.dir; //dir to scene
	t_vec	u = norm_vec(vec_cross(0, 1, 0), w); //relative x axis
	t_vec	v = vec_cross(w, u); //relative y axis;

	t_vec	hori = mult_vec(u, v_wide);
	t_vec	verti = mult_vec(v, -v_high);
	t_vec	px = div_vec(hori, (double)WIDTH);
	t_vec	py = div_vec(verti, (double)HEIGHT);





    ////meeeeeeh a refaire un ayant une meilleure idee
    if (fabs(data->cam.dir.y) > 1.0 - 1e-4)
    {
        data->view.hori = mult_vec(norm_vec(vec_cross(
            data->cam.dir, (t_vec){0, 0, -1.0})), tan((double)deg_to_rad(data->cam.fov) / 2.0));
    }
    else
        data->view.hori = mult_vec(norm_vec(vec_cross(
            data->cam.dir, (t_vec){0, 1.0, 0})), tan((double)deg_to_rad(data->cam.fov) / 2.0));
    data->view.verti = mult_vec(norm_vec(vec_cross(
        data->view.hori, data->cam.dir)) , len_vec(data->view.hori) * HEIGHT / WIDTH);
    data->view.pos = add_vec(add_vec(data->cam.pos, data->cam.dir), add_vec(data->view.hori, data->view.verti));
}