#include "./includes/miniRT.h"

void    get_viewport(t_data *data)
{

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