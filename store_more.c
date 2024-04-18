/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   store_more.c									   :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:47:35 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:36 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	manage_ambiant(char **tab, t_data *data, int split_count)
{
	if (data->amli.init == 1 || split_count != 3)
		ft_error_exit("Wrong file format : amb", data);
	data->amli.init = 1;
	if (ft_atob(tab[1], 1, 2, &data->amli.ratio) == -1
		|| data->amli.ratio < 0 || data->amli.ratio > 1)
		ft_error_exit("Wrong file format : amb", data);
	manage_rgb(tab, &data->amli.color, data, 2);
	data->amli.color = mult_rgb_dub(data->amli.color, (data->amli.ratio));
}

void	manage_cam(char **tab, t_data *data, int split_count)
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

void	manage_background(char **tab, t_data *data, int split_count)
{
	if (split_count != 3)
		ft_error_exit("Wrong file format : background", data);
	manage_rgb(tab, &data->back_1, data, 1);
	manage_rgb(tab, &data->back_2, data, 2);
	data->back_set = 1;
}

void	add_cyl(t_data *data, t_cyl *cyl)
{
	t_cyl	*temp;

	cyl->dir = norm_vec(cyl->dir);
	cyl->next = NULL;
	if (data->cyl == NULL)
		data->cyl = cyl;
	else
	{
		temp = data->cyl;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = cyl;
	}
}

void	manage_cyl(char **tab, t_data *data, int split_count)
{
	t_cyl	*new;

	if (split_count != 6 && split_count != 7)
		ft_error_exit("Wrong file format : cyl", data);
	new = gc_malloc(sizeof(t_cyl), data);
	manage_vectors(tab, &new->pos, data, 1);
	manage_vectors(tab, &new->dir, data, 2);
	if (new->dir.x > 1 || new->dir.y > 1 || new->dir.z > 1
		|| new->dir.x < 0 || new->dir.y < 0 || new->dir.z < 0)
		ft_error_exit("Wrong file format : cyl", data);
	if (ft_atob(tab[3], 2, 3, &new->diam) == -1 || new->diam <= 0)
		ft_error_exit("Wrong file format : cyl diam", data);
	if (ft_atob(tab[4], 2, 3, &new->height) == -1 || new->height <= 0)
		ft_error_exit("Wrong file format : cyl height", data);
	manage_rgb(tab, &new->rgb, data, 5);
	if (ft_atob(tab[6], 1, 3, &new->mat) == -1)
		ft_error_exit("Wrong file format : cyl", data);
	add_cyl(data, new);
}
