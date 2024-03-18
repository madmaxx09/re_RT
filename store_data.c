#include "./includes/miniRT.h"

//dont forget to procect every read from a tabl

void manage_ambiant(char **tab, t_data *data)
{
	if (data->amli.init == 1)
		ft_error_exit("Wrong file format");
	data->amli.init = 1;
	if (ft_atob(tab[1], 1, 2, &data->amli.ratio) == -1 
		|| data->amli.ratio < 0 || data->amli.ratio > 1)
		ft_error_exit("Wrong file format");
	manage_rgb(tab, data->amli.color, data, 2);
}

void manage_cam(char **tab, t_data *data)
{
	if (data->cam.init == 1)
		ft_error_exit("Wrong file format");
	data->cam.init = 1;
	manage_vectors(tab, &data->cam.pos, data, 1);
	manage_vectors(tab, &data->cam.dir, data, 2);
	if (data->cam.dir.x > 1 || data->cam.dir.y > 1 || data->cam.dir.z > 1 
		|| data->cam.dir.x < 0 || data->cam.dir.y < 0 || data->cam.dir.z < 0)
		ft_error_exit("Wrong file format");
	data->cam.fov = ft_atoi(tab[3]);
	if (data->cam.fov > 180 || data->cam.fov < 0)
		ft_error_exit("Wrong file format");
}

void manage_light(char **tab, t_data *data)
{
	if (data->light.init == 1)
		ft_error_exit("Wrong file format");
	data->light.init = 1;
	manage_vectors(tab, &data->light.pos, data, 1);
	if (ft_atob(tab[2], 1, 2, &data->light.ratio) == -1
	 || data->light.ratio < 0 || data->light.ratio > 1)
		ft_error_exit("Wrong file format");
	manage_rgb(tab, data->light.rgb, data, 3);
}

void manage_sphere(char **tab, t_data *data)
{
	t_sphere *new;
	t_sphere *temp;

	new = gc_malloc(sizeof(t_sphere), data);
	manage_vectors(tab, &new->pos, data, 1);
	if (ft_atob(tab[2], 1, 2, &new->diam) == -1)
		ft_error_exit("Wrong file format");
	if (new->rad <= 0)
		ft_error_exit("Wrong file format");
	manage_rgb(tab, &new->rgb, data, 3);
	if (data->sphere == NULL)
		data->sphere = new;
	else
	{
		temp = data->sphere;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void manage_plan(char **tab, t_data *data)
{  
	t_plan	*new;
	t_plan	*temp;

	new = gc_malloc(sizeof(t_plan), data);
	manage_vectors(tab, &new->pos, data, 1);
	manage_vectors(tab, &new->dir, data, 2);
	if (new->dir.x > 1 || new->dir.y > 1 || new->dir.z > 1 
		|| new->dir.x < -1 || new->dir.y < -1 || new->dir.z < -1)
		ft_error_exit("Wrong file format");
	manage_rgb(tab, &new->rgb, data, 3);
	if (data->plan == NULL)
		data->plan = new;
	else
	{
		temp = data->plan;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}