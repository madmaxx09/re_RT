/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:38:36 by mdor              #+#    #+#             */
/*   Updated: 2024/04/18 19:38:37 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

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

void	add_sph(t_data *data, t_sphere *sph)
{
	t_sphere	*temp;

	sph->next = NULL;
	if (data->sphere == NULL)
		data->sphere = sph;
	else
	{
		temp = data->sphere;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = sph;
	}
}

void	add_pl(t_data *data, t_plan *pln)
{
	t_plan	*temp;

	pln->next = NULL;
	if (data->plan == NULL)
		data->plan = pln;
	else
	{
		temp = data->plan;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = pln;
	}
}
