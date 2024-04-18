/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   parse.c											:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:46:38 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:46:40 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	check_format(char *rt_file, t_data *data)
{
	int	i;

	i = ft_strlen(rt_file);
	if (i <= 3)
		ft_error_exit("Wrong file format", data);
	if (rt_file[i - 1] != 't'
		|| rt_file[i - 2] != 'r' || rt_file[i - 3] != '.')
		ft_error_exit("Wrong file format", data);
}

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
	t_disc	*new;
	t_disc	*tmp;

	new = gc_malloc(sizeof(t_disc), data);
	new->diam = cyl->diam;
	new->dir = cyl->dir;
	if (top_bot == 0)
		new->pos = lin_comb(1.0, cyl->pos, (cyl->height / 2.0), cyl->dir);
	else
		new->pos = lin_comb(1.0, cyl->pos, (cyl->height / -2.0), cyl->dir);
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
	t_data	tmp;

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
		if (line[0] != '\n' && line[0] != '\0')
			process_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	if (data->cyl != NULL)
		get_cyl_top_bot(data);
	if (data->back_set == 0)
	{
		data->back_1 = data->amli.color;
		data->back_2 = data->amli.color;
	}
}
