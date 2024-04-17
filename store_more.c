/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:47:35 by mdor              #+#    #+#             */
/*   Updated: 2024/04/17 19:47:36 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void    manage_background(char **tab, t_data *data, int split_count)
{
    if (split_count != 3)
        ft_error_exit("Wrong file format : background", data);
    manage_rgb(tab, &data->back_1, data, 1);
    manage_rgb(tab, &data->back_2, data, 2);
    data->back_set = 1;
}

int	int_from_str(const char *str, int min, int max, int *res)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	*res = ft_atoi(str);
	if (*res < min || *res > max)
		return (-1);
	return (0);
}

void    manage_cyl(char **tab, t_data *data, int split_count)
{
    t_cyl   *new;
    t_cyl   *temp;

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
    new->dir = norm_vec(new->dir);
    new->next = NULL;
    if (data->cyl == NULL)
        data->cyl = new;
    else
    {
        temp = data->cyl;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}
