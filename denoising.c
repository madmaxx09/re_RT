/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   denoising.c										:+:	  :+:	:+:   	  */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:45:35 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:45:37 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

//idee de base serait de faire une moyenne 
//des couleurs des pixels ajdacents dans une seule boucle
//en donnant probablement (beaucoup ?) moins de poids aux pixels noirs 

//mediane plus performante sur les bords/details
//faire moins peser les coefficients avec 
//une longueur d'onde basse est plus efficace car ils representent
//souvent des zones avec plus de bruit 

//seul probleme c'est que pour appliquer cette 
//methode je vais devoir map mes pixels dans un tableau au lieu de les afficher
//immediatement

inline bool	is_black(t_rgb pixel)
{
	if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0)
		return (true);
	return (false);
}

inline double	gaus_w(int x, int y, double sigma)
{
	return (exp(-((x * x + y * y) / (2 * sigma * sigma))));
}

//ici faire une moyenne (mediane) 
//et compter les pixels noir return l'un ou l'autre en fonction
//the bigger the threshold the less black is ignored
	//block = total_black(j, i, image);
// if (block && is_black(image[(j + k) * WIDTH + (i + l)]))
// {
// 	l++;
// 	continue;
// }
int	total_black(int j, int i, t_rgb *image)
{
	double	t;
	int		k;
	int		l;

	t = 0;
	k = -1 * DENOISE_SAMPLE;
	while (k <= DENOISE_SAMPLE)
	{
		l = -1 * DENOISE_SAMPLE;
		while (l <= DENOISE_SAMPLE)
		{
			if (j + k >= 0 && j + k < HEIGHT && i + l >= 0 && i + l < WIDTH)
			{
				if (is_black(image[(j + k) * WIDTH + (i + l)]))
					t++;
			}
			l++;
		}
		k++;
	}
	if ((t / SQUARE_AREA) < BLACK_TRESHHOLD)
		return (1);
	return (0);
}

t_rgb	denoise_pixel(int j, int i, t_rgb *image)
{
	int		k;
	int		l;
	double	total_w;
	t_rgb	blend;

	blend = (t_rgb){0, 0, 0};
	k = -1 * DENOISE_SAMPLE;
	total_w = 0.0;
	while (k <= DENOISE_SAMPLE)
	{
		l = -1 * DENOISE_SAMPLE;
		while (l <= DENOISE_SAMPLE)
		{
			if (j + k >= 0 && j + k < HEIGHT && i + l >= 0 && i + l < WIDTH)
			{
				blend = (add_rgbs(blend,
							mult_rgb_dub(image[(j + k) * WIDTH + (i + l)],
								gaus_w(abs(k), abs(l), DENOISE_SIGMA))));
				total_w += gaus_w(abs(k), abs(l), DENOISE_SIGMA);
			}
			l++;
		}
		k++;
	}
	return (div_rgb(blend, total_w));
}

void	denoise_and_render(t_data *data)
{
	t_rgb	*denoised;
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("denoise\n");
	denoised = malloc(sizeof(t_rgb) * WIDTH * HEIGHT);
	ft_bzero(denoised, sizeof(t_rgb) * WIDTH * HEIGHT);
	while (j < HEIGHT)
	{
		while (i < WIDTH)
		{
			denoised[j * WIDTH + i] = denoise_pixel(j, i, data->image);
			i++;
		}
		i = 0;
		j++;
	}
	assign_img(data, denoised);
	free(denoised);
}
