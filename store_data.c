#include "./includes/miniRT.h"

//dont forget to procect every read from a tabl

void manage_ambiant(char **tab, t_data *data)
{
	if (data->amli.init == 1)
		ft_error_exit("Wrong file format : amb", data);
	data->amli.init = 1;
	if (ft_atob(tab[1], 1, 2, &data->amli.ratio) == -1 
		|| data->amli.ratio < 0 || data->amli.ratio > 1)
		ft_error_exit("Wrong file format : amb", data);
	manage_rgb(tab, &data->amli.color, data, 2);
	data->amli.color = mult_rgb_dub(data->amli.color, data->amli.ratio);
}

void manage_cam(char **tab, t_data *data)
{
	if (data->cam.init == 1)
		ft_error_exit("Wrong file format : cam", data);
	data->cam.init = 1;
	manage_vectors(tab, &data->cam.pos, data, 1);
	manage_vectors(tab, &data->cam.dir, data, 2);
	if (data->cam.dir.x > 1 || data->cam.dir.y > 1 || data->cam.dir.z > 1 
		|| data->cam.dir.x < -1 || data->cam.dir.y < -1 || data->cam.dir.z < -1)
		ft_error_exit("Wrong file format : cam", data);
	data->cam.fov = ft_atoi(tab[3]);
	if (data->cam.fov > 180 || data->cam.fov < 0)
		ft_error_exit("Wrong file format : cam", data);
}

void	map_brightness(t_rgb *store, char *brightness, t_data *data, char **tab)
{
	t_rgb color;
	double bright;

	ft_atob(brightness, 1, 2, &bright);
	color = (t_rgb){1,1,1};
	if (tab != NULL)
		manage_rgb(tab, &color, data, 3);
	if (bright > 1 || bright < 0)
		ft_error_exit("Wrong file format : bright", data);
	store->r = (color.r * 5 * bright);
	store->g = (color.g * 5 * bright);
	store->b = (color.b * 5 * bright);
}

//on va se dire qu'une luminosité nulle (0) = {1,1,1} et mapper ca jusque 5 pour le moment donc luminosite 1 = {5,5,5}
//puis faire scale chaque composante de cette lumiere is rgb est spécifié dans le pdf 
//taille de sphere de lum set a 1 de diametre
//je pourrais me faire chier a faire de chaque objet une source de lumiere mais on verra plus tard 
void manage_light(char **tab, t_data *data) //will have the option to specify the size or not
{
	int i;
	t_sphere *new;
	t_sphere *tmp;

	i = 0;
	new = gc_malloc(sizeof(t_sphere), data);
	manage_vectors(tab, &new->pos, data, 1);
	new->diam = 1; //1 pour le moment on verra comment adapter
	// if (ft_atob(tab[3], 10,3, &new->diam) == -1)
	// 	ft_error_exit("Wrong file format : light", data);
	while (tab[i])
		i++;
	if (i <= 4)
		map_brightness(&new->rgb, tab[2], data, NULL);
	else
		map_brightness(&new->rgb, tab[2], data, tab);
	print_rgb(new->rgb);
	new->mat = 3;
	new->next = NULL;
	if (data->sphere == NULL)
		data->sphere = new;
	else
	{
		tmp = data->sphere;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void manage_sphere(char **tab, t_data *data)
{
	t_sphere *new;
	t_sphere *temp;

	new = gc_malloc(sizeof(t_sphere), data);
	manage_vectors(tab, &new->pos, data, 1);
	if (ft_atob(tab[2], 10, 3, &new->diam) == -1)
		ft_error_exit("Wrong file format : sp", data);
	if (new->diam <= 0)
		ft_error_exit("Wrong file format : sp", data);
	manage_rgb(tab, &new->rgb, data, 3);
	if (ft_atob(tab[4], 1, 3, &new->mat) == -1)
		ft_error_exit("Wrong file format : sp", data);
	new->next = NULL;
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
		ft_error_exit("Wrong file format : pl", data);
	//new->dir = norm_vec(new->dir);
	manage_rgb(tab, &new->rgb, data, 3);
	if (ft_atob(tab[4], 1, 3, &new->mat) == -1)
		ft_error_exit("Wrong file format : pl", data);
	new->next = NULL;
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