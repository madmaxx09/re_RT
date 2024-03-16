#include "./includes/miniRT.h"

void	ft_error_exit(char *str, t_data *data)
{

}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->wind = NULL;
	data->sphere = NULL;
	data->plan = NULL;
	data->cyl = NULL;
	data->error_trigger = 0;
}

void	check_format(char *rt_file, t_data *data)
{
	int i;

	i = ft_strlen(rt_file);
	if (i <= 3)
		ft_error_exit("Wrong file format", data);
	if (rt_file[i] != "t" 
		|| rt_file[i - 1] != "r" || rt_file[i - 2] != ".")
		ft_error_exit("Wrong file format", data);
}

void	parse_rt(char *rt_file, t_data *data)
{
	int		fd;
	char	*line;
	int		error;
	
	error = 0;
	check_format(rt_file, data);
	fd = open(rt_file, O_RDONLY);
	if (fd == -1)
		ft_error_exit(strerror(errno), data);
	line = get_next_line(fd);
	while (line)
	{
		error = process_line(line, data);
		free(line);
		if (error == 1)
			ft_error_exit("Wrong file format", data);
		line = get_next_line(fd);
	}
}

int main (int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error_exit("This program needs 1 file as argument", &data);
	init_data(&data);
	parse_rt(argv[1], &data);
}
