/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:47:27 by mdor              #+#    #+#             */
/*   Updated: 2024/04/17 19:47:31 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void manage_ambiant(char **tab, t_data *data, int split_count)
{
	if (data->amli.init == 1 || split_count != 3)
		ft_error_exit("Wrong file format : amb", data);
	data->amli.init = 1;
	if (ft_atob(tab[1], 1, 2, &data->amli.ratio) == -1 
		|| data->amli.ratio < 0 || data->amli.ratio > 1)
		ft_error_exit("Wrong file format : amb", data);
	manage_rgb(tab, &data->amli.color, data, 2);
	data->amli.color = mult_rgb_dub(data->amli.color, data->amli.ratio);
}

void manage_cam(char **tab, t_data *data, int split_count)
{
	if (data->cam.init == 1 || split_count != 4)
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

int is_rgb(char *rgb, t_data *data)
{
	char **tmp;
	t_rgb test;

	tmp = ft_split(rgb, ',');
	if (ft_split_counter(tmp) != 3)
		return (0);
	ft_atob(tmp[0], 1, 2, &test.r);
    ft_atob(tmp[1], 1, 2, &test.g);
    ft_atob(tmp[2], 1, 2, &test.b);
	if (test.r > 255 || test.g > 255 || test.b > 255 
        || test.r < 0 || test.g < 0 || test.b < 0)
        ft_error_exit("Wrong file format : rgb", data);
	return (1);
}

void	map_brightness(t_sphere *sphere, char *brightness, t_data *data, char **tab, int split_count)
{
	t_rgb color;
	double bright;

	ft_atob(brightness, 1, 2, &bright);
	color = (t_rgb){1,1,1};
	if (bright > 1 || bright < 0)
		ft_error_exit("Wrong file format : bright", data);
	if (split_count > 3 && is_rgb(tab[3], data))
		manage_rgb(tab, &color, data, 3);
	if (split_count > 3 && !is_rgb(tab[3], data))
	{
		if (ft_atob(tab[3], 10, 3, &sphere->diam) == -1 || sphere->diam <= 0)
			ft_error_exit("Wrong file format : light", data);
	}
	else if (split_count == 5)
	{
		if (ft_atob(tab[4], 10, 3, &sphere->diam) == -1 || sphere->diam <= 0)
			ft_error_exit("Wrong file format : light", data);
	}
	sphere->rgb.r = (color.r * 5 * bright);
	sphere->rgb.g = (color.g * 5 * bright);
	sphere->rgb.b = (color.b * 5 * bright);
}

//on va se dire qu'une luminosité nulle (0) = {1,1,1} et mapper ca jusque 5 pour le moment donc luminosite 1 = {5,5,5}
//puis faire scale chaque composante de cette lumiere is rgb est spécifié dans le pdf 
//taille de sphere de lum set a 1 de diametre
//je pourrais me faire chier a faire de chaque objet une source de lumiere mais on verra plus tard 
void manage_light(char **tab, t_data *data, int split_count) //will have the option to specify the size or not
{
	t_sphere *new;
	t_sphere *tmp;

	new = gc_malloc(sizeof(t_sphere), data);
	if (split_count < 3 || split_count > 5)
		ft_error_exit("Wrong file format : light", data);
	manage_vectors(tab, &new->pos, data, 1);
	new->diam = 1;
	map_brightness(new, tab[2], data, tab, split_count);
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

void manage_sphere(char **tab, t_data *data, int split_count)
{
	t_sphere *new;
	t_sphere *temp;

	if (split_count != 4 && split_count != 5)
		ft_error_exit("Wrong file format : sp", data);
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

void manage_plan(char **tab, t_data *data, int split_count)
{  
	t_plan	*new;
	t_plan	*temp;

	if (split_count != 4 && split_count != 5)
		ft_error_exit("Wrong file format : pl", data);
	new = gc_malloc(sizeof(t_plan), data);
	manage_vectors(tab, &new->pos, data, 1);
	manage_vectors(tab, &new->dir, data, 2);
	if (new->dir.x > 1 || new->dir.y > 1 || new->dir.z > 1 
		|| new->dir.x < -1 || new->dir.y < -1 || new->dir.z < -1)
		ft_error_exit("Wrong file format : pl", data);
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
