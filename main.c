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

int main (int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error_exit("This program needs 1 file as argument", &data);
	init_data(&data);
	parse_rt(argv[1], &data);
}