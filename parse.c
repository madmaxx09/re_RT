/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:46:38 by mdor              #+#    #+#             */
/*   Updated: 2024/04/17 19:46:40 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	check_format(char *rt_file, t_data *data)
{
	int i;

	i = ft_strlen(rt_file);
	if (i <= 3)
		ft_error_exit("Wrong file format", data);
	if (rt_file[i - 1] != 't' 
		|| rt_file[i - 2] != 'r' || rt_file[i - 3] != '.')
		ft_error_exit("Wrong file format", data);
}

//peut etre un monde ou si bcp de sphere/objets j'alloue la taille totale necessaire un un shot puis je la fragmente
//afin que quand on cherche dans cette liste d'objets toute la memoire vienne en cache (rien n'est sur)

void	process_line(char *line, t_data *data)
{
	char	**tab;
	tab = ft_split(line, ' ');
	if (ft_strcmp(tab[0], "A") == 0)
		manage_ambiant(tab, data, ft_split_counter(tab));
	else if (ft_strcmp(tab[0], "C") == 0)
		manage_cam(tab, data, ft_split_counter(tab));
	else if (ft_strcmp(tab[0], "L") == 0)
		manage_light(tab, data, ft_split_counter(tab));
	else if (ft_strcmp(tab[0], "sp") == 0)
		manage_sphere(tab, data, ft_split_counter(tab));
	else if (ft_strcmp(tab[0], "pl") == 0)
		manage_plan(tab, data, ft_split_counter(tab));
	else if (ft_strcmp(tab[0], "cy") == 0)
		manage_cyl(tab, data, ft_split_counter(tab));
	else if (ft_strcmp(tab[0], "B") == 0)
		manage_background(tab, data, ft_split_counter(tab));
	else
		ft_error_exit("Wrong file format : wrong first char", data);
	free_tabl(tab);
}

void	add_discs(t_cyl *cyl, t_data *data, int top_bot)
{
	t_disc *new;
	t_disc *tmp;

	new = gc_malloc(sizeof(t_disc), data);
	new->diam = cyl->diam;
	new->dir = cyl->dir;
	if (top_bot == 0)
		new->pos = lin_comb(1.0, cyl->pos, (cyl->height / 2.0), cyl->dir);
	else
		new->pos = new->pos = lin_comb(1.0, cyl->pos, (cyl->height / -2.0), cyl->dir);
	new->next = NULL;
	new->rgb = cyl->rgb;
	new->mat = cyl->mat;
	if (data->disc == NULL)
		data->disc = new;
	else
	{
		tmp = data->disc;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	get_cyl_top_bot(t_data *data)
{
	t_data tmp;

	tmp = *data;
	while (tmp.cyl != NULL)
	{
		add_discs(tmp.cyl, data, 0);
		add_discs(tmp.cyl, data, 1);
		tmp.cyl = tmp.cyl->next;
	}	
}

void	parse_rt(char *rt_file, t_data *data)
{
	int		fd;
	char	*line;
	
	check_format(rt_file, data);
	fd = open(rt_file, O_RDONLY);
	if (fd == -1)
		ft_error_exit(strerror(errno), data);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	if (data->cyl != NULL)
		get_cyl_top_bot(data);
}
















void print_args(t_data *data)
{
    // printf("Ambient Light:\n");
    // printf("\tRatio: %f\n", data->amli.ratio);
    // printf("\tColor: R: %f, G: %f, B: %f\n", data->amli.color.r, data->amli.color.g, data->amli.color.b);

    // printf("Camera:\n");
    // printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->cam.pos.x, data->cam.pos.y, data->cam.pos.z);
    // printf("\tVector: X: %f, Y: %f, Z: %f\n", data->cam.dir.x, data->cam.dir.y, data->cam.dir.z);
    // printf("\tFOV: %d\n", data->cam.fov);

    // printf("Light:\n");
    // printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->light.pos.x, data->light.pos.y, data->light.pos.z);
    // printf("\tLighting: %f\n", data->light.ratio);

    printf("Spheres:\n");
	while(data->sphere)
	{
        printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->sphere->pos.x, data->sphere->pos.y, data->sphere->pos.z);
        printf("\tDiameter: %f\n", data->sphere->diam);
        printf("\tColor: R: %f, G: %f, B: %f\n", data->sphere->rgb.r, data->sphere->rgb.g, data->sphere->rgb.b);
		printf ("\tMat : %f\n", data->sphere->mat);
		data->sphere = data->sphere->next;
	}

    printf("Viewport:\n");
    // printf("\tHorizontal Vector: X: %f, Y: %f, Z: %f\n", data->view.hori.x, data->view.hori.y, data->view.hori.z);
    // printf("\tVertical Vector: X: %f, Y: %f, Z: %f\n", data->view.verti.x, data->view.verti.y, data->view.verti.z);
    printf("\tX Pixel Vector: X: %f, Y: %f, Z: %f\n", data->view.x_pix.x, data->view.x_pix.y, data->view.x_pix.z);
    printf("\tY Pixel Vector: X: %f, Y: %f, Z: %f\n", data->view.y_pix.x, data->view.y_pix.y, data->view.y_pix.z);
    printf("\tPixel 00: X: %f, Y: %f, Z: %f\n", data->view.pix00.x, data->view.pix00.y, data->view.pix00.z);

    printf("Plans:\n");
    printf("\tPosition: X: %f, Y: %f, Z: %f\n", data->plan->pos.x, data->plan->pos.y, data->plan->pos.z);
    printf("\tVector: X: %f, Y: %f, Z: %f\n", data->plan->dir.x, data->plan->dir.y, data->plan->dir.z);
    printf("\tColor: R: %f, G: %f, B: %f\n", data->plan->rgb.r, data->plan->rgb.g, data->plan->rgb.b);
}
