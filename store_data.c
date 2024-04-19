/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   store_data.c									   :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:47:27 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:31 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

int	is_rgb(char *rgb, t_data *data, char **tab)
{
	char	**tmp;
	t_rgb	test;

	tmp = ft_split(rgb, ',');
	if (ft_split_counter(tmp) != 3)
		return (0);
	ft_atob(tmp[0], 1, 2, &test.r);
	ft_atob(tmp[1], 1, 2, &test.g);
	ft_atob(tmp[2], 1, 2, &test.b);
	free_tabl(tmp);
	if (test.r > 255 || test.g > 255 || test.b > 255
		|| test.r < 0 || test.g < 0 || test.b < 0)
		ft_error_exit("Error\nWrong file format : rgb", data, tab);
	return (1);
}

void	map_brightness(t_sphere *sphere,
		t_data *data, char **tab, int split_count)
{
	t_rgb	color;
	double	bright;

	ft_atob(tab[2], 1, 2, &bright);
	color = (t_rgb){1, 1, 1};
	if (bright > 1 || bright < 0)
		ft_error_exit("Error\nWrong file format : bright", data, tab);
	if (split_count > 3 && is_rgb(tab[3], data, tab))
		manage_rgb(tab, &color, data, 3);
	if (split_count > 3 && !is_rgb(tab[3], data, tab))
	{
		if (ft_atob(tab[3], 10, 3, &sphere->diam) == -1 || sphere->diam <= 0)
			ft_error_exit("Error\nWrong file format : light", data, tab);
	}
	else if (split_count == 5)
	{
		if (ft_atob(tab[4], 10, 3, &sphere->diam) == -1 || sphere->diam <= 0)
			ft_error_exit("Error\nWrong file format : light", data, tab);
	}
	sphere->rgb.r = (color.r * 5 * bright);
	sphere->rgb.g = (color.g * 5 * bright);
	sphere->rgb.b = (color.b * 5 * bright);
}

//on va se dire qu'une luminosité nulle (0) = {1,1,1} 
//et mapper ca jusque 5 pour le moment donc luminosite 1 = {5,5,5}
//puis faire scale chaque composante de 
//cette lumiere is rgb est spécifié dans le pdf 
//taille de sphere de lum set a 1 de diametre
//je pourrais me faire chier a faire de chaque objet 
//une source de lumiere mais on verra plus tard 
void	manage_light(char **tab, t_data *data, int split_count)
{
	t_sphere	*new;
	t_sphere	*tmp;

	new = gc_malloc(sizeof(t_sphere), data);
	if (split_count < 3 || split_count > 5)
		ft_error_exit("Error\nWrong file format : light", data, tab);
	manage_vectors(tab, &new->pos, data, 1);
	new->diam = 1;
	map_brightness(new, data, tab, split_count);
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

void	manage_sphere(char **tab, t_data *data, int split_count)
{
	t_sphere	*new;

	if (split_count != 4 && split_count != 5)
		ft_error_exit("Error\nWrong file format : sp", data, tab);
	new = gc_malloc(sizeof(t_sphere), data);
	manage_vectors(tab, &new->pos, data, 1);
	if (ft_atob(tab[2], 10, 3, &new->diam) == -1)
		ft_error_exit("Error\nWrong file format : sp", data, tab);
	if (new->diam <= 0)
		ft_error_exit("Error\nWrong file format : sp", data, tab);
	manage_rgb(tab, &new->rgb, data, 3);
	new->mat = 2.0;
	if (split_count == 5)
		if (ft_atob(tab[4], 1, 3, &new->mat) == -1
			|| new->mat < 0 || (new->mat > 1 && new->mat != 2 && new->mat != 3))
			ft_error_exit("Error\nWrong file format : sp", data, tab);
	add_sph(data, new);
}

void	manage_plan(char **tab, t_data *data, int split_count)
{
	t_plan	*new;

	if (split_count != 4 && split_count != 5)
		ft_error_exit("Error\nWrong file format : pl", data, tab);
	new = gc_malloc(sizeof(t_plan), data);
	manage_vectors(tab, &new->pos, data, 1);
	manage_vectors(tab, &new->dir, data, 2);
	if (new->dir.x > 1 || new->dir.y > 1 || new->dir.z > 1
		|| new->dir.x < -1 || new->dir.y < -1 || new->dir.z < -1)
		ft_error_exit("Error\nWrong file format : pl", data, tab);
	manage_rgb(tab, &new->rgb, data, 3);
	new->mat = 2.0;
	if (split_count == 5)
		if (ft_atob(tab[4], 1, 3, &new->mat) == -1
			|| new->mat < 0 || (new->mat > 1 && new->mat != 2 && new->mat != 3))
			ft_error_exit("Error\nWrong file format : pl", data, tab);
	add_pl(data, new);
}
