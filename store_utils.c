/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   store_utils.c									  :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:47:46 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:47:47 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	free_tabl(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	manage_rgb(char **tab, t_rgb *store, t_data *data, int pos)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(tab[pos], ',');
	while (tmp[i])
		i++;
	if (i != 3)
		ft_error_exit("Wrong file format : rgb", data);
	ft_atob(tmp[0], 1, 2, &store->r);
	ft_atob(tmp[1], 1, 2, &store->g);
	ft_atob(tmp[2], 1, 2, &store->b);
	if (store->r > 255 || store->g > 255 || store->b > 255
		|| store->r < 0 || store->g < 0 || store->b < 0)
		ft_error_exit("Wrong file format : rgb", data);
	store->r = (store->r / 255);
	store->g = (store->g / 255);
	store->b = (store->b / 255);
	free_tabl(tmp);
}

void	manage_vectors(char **tab, t_vec *store, t_data *data, int pos)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(tab[pos], ',');
	while (tmp[i])
		i++;
	if (i != 3)
		ft_error_exit("Wrong file format", data);
	ft_atob(tmp[0], 10, 2, &store->x);
	ft_atob(tmp[1], 10, 2, &store->y);
	ft_atob(tmp[2], 10, 2, &store->z);
	free_tabl(tmp);
}
