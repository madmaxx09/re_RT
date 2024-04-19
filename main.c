/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:45:49 by mdor              #+#    #+#             */
/*   Updated: 2024/04/17 19:45:50 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	ft_error_exit(char *str, t_data *data, char **tab)
{
	if (tab != NULL)
		free_tabl(tab);
	ft_printf("%s\n", str);
	free(data->image);
	free_custom_alloc(data);
	exit(1);
}

void	init_data(t_data *data)
{
	data->cam.init = 0;
	data->amli.init = 0;
	data->light.init = 0;
	data->mlx = NULL;
	data->wind = NULL;
	data->sphere = NULL;
	data->plan = NULL;
	data->cyl = NULL;
	data->disc = NULL;
	data->error_trigger = 0;
	data->image = (t_rgb *)malloc(sizeof(t_rgb) * WIDTH * HEIGHT);
	ft_bzero(data->image, sizeof(t_rgb) * WIDTH * HEIGHT);
	data->back_set = 0;
	data->back_2 = (t_rgb){0, 0, 0};
	data->back_1 = (t_rgb){0, 0, 0};
}

int	closing(t_data *data)
{
	ft_error_exit("Program closed", data, NULL);
	exit(EXIT_SUCCESS);
}

void	mlx_launch(t_data *data)
{
	int	i;

	i = -1;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		ft_error_exit("Error\nMlx init fail", data, NULL);
	data->wind = mlx_new_window(data->mlx, WIDTH, HEIGHT, "MiniRT");
	if (data->wind == NULL)
		ft_error_exit("Error\nMlx init fail", data, NULL);
	get_viewport(data);
	raytrace(data);
	while (++i < DENOISE_PASS)
		denoise_and_render(data);
	print_image(data->image, data);
	mlx_hook(data->wind, 17, 0, closing, data);
	mlx_key_hook(data->wind, presskey, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_error_exit("Error\nThis program needs 1 file as argument",
			&data, NULL);
	}
	init_data(&data);
	parse_rt(argv[1], &data);
	printf("HEIGHT = %f\n", HEIGHT);
	printf("WIDTH = %d\n", WIDTH);
	printf("DEPTH = %d\n", MAX_DEPTH);
	printf("SAMPLE = %d\n", SAMPLE);
	printf("DENOISE_PASS = %d\n", DENOISE_PASS);
	printf("DENOISE_SIGMA = %f\n", DENOISE_SIGMA);
	printf("DENOISE_SAMPLE = %f\n", DENOISE_SAMPLE);
	mlx_launch(&data);
}
