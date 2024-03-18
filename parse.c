#include "miniRT.h"

void	check_format(char *rt_file, t_data *data)
{
	int i;

	i = ft_strlen(rt_file);
	if (i <= 3)
		ft_error_exit("Wrong file format", data);
	if (rt_file[i] != "t" 
		|| rt_file[i - 1] != "r" || rt_file[i - 2] != ".")
		ft_error_exit("Wrong file format", data);
}

void	process_line(char *line, t_data *data)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (ft_strcmp(tab[0], "A") == 0)
		manage_ambiant(tab, data);
	else if (ft_strcmp(tab[0], "C") == 0)
		manage_cam(tab, data);
	else if (ft_strcmp(tab[0], "L") == 0)
		manage_light(tab, data);
	else if (ft_strcmp(tab[0], "sp") == 0)
		manage_sphere(tab, data);
	else if (ft_strcmp(tab[0], "pl") == 0)
		manage_plan(tab, data);
	// else if (ft_strcmp(tab[0], "cy") == 0)
	// 	manage_cyl(tab, data);
	else
		ft_error_exit("Wrong file format");
	free_tabl(tab);
}

void	parse_rt(char *rt_file, t_data *data)
{
	int		fd;
	char	*line;
	int		error;
	
	error = 0;
	check_format(rt_file, data);
	fd = open(rt_file, O_RDONLY);
	if (fd == -1)
		ft_error_exit(strerror(errno), data);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, data);
		free(line);
		if (error == 1)
			ft_error_exit("Wrong file format", data);
		line = get_next_line(fd);
	}
}
















void print_args(t_data *data)
{
    // Print ambient light details
    printf("Ambient Light:\n");
    printf("\tRatio: %f\n", data->amli.ratio);
    printf("\tColor: R: %d, G: %d, B: %d\n", data->amli.r, data->amli.g, data->amli.b);

    // Print camera details
    printf("Camera:\n");
    printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->cam.x_ax, data->cam.y_ax, data->cam.z_ax);
    printf("\tVector: X: %f, Y: %f, Z: %f\n", data->cam.vec_x, data->cam.vec_y, data->cam.vec_z);
    printf("\tFOV: %d\n", data->cam.fov);

    // Print light details
    printf("Light:\n");
    printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->light.x_ax, data->light.y_ax, data->light.z_ax);
    printf("\tLighting: %f\n", data->light.lighting);

    // Print spheres
    printf("Spheres:\n");
    while (data->sphere != NULL) {
        printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->sphere->x_ax, data->sphere->y_ax, data->sphere->z_ax);
        printf("\tDiameter: %f\n", data->sphere->diameter);
        printf("\tColor: R: %d, G: %d, B: %d\n", data->sphere->r, data->sphere->g, data->sphere->b);
        data->sphere = data->sphere->next;
    }

    // Print plans
    printf("Plans:\n");
    t_plan *current_plan = data->plan;
    while (current_plan != NULL) {
        printf("\tPosition: X: %f, Y: %f, Z: %f\n", current_plan->x_ax, current_plan->y_ax, current_plan->z_ax);
        printf("\tVector: X: %f, Y: %f, Z: %f\n", current_plan->vec_x, current_plan->vec_y, current_plan->vec_z);
        printf("\tColor: R: %d, G: %d, B: %d\n", current_plan->r, current_plan->g, current_plan->b);
        current_plan = current_plan->next;
    }
}