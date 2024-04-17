/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   denoising.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:45:35 by mdor              #+#    #+#             */
/*   Updated: 2024/04/17 19:45:37 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"


//idee de base serait de faire une moyenne des couleurs des pixels ajdacents dans une seule boucle
//en donnant probablement (beaucoup ?) moins de poids aux pixels noirs 

//mediane plus performante sur les bords/details
//faire moins peser les coefficients avec une longueur d'onde basse est plus efficace car ils representent
//souvent des zones avec plus de bruit 

//seul probleme c'est que pour appliquer cette methode je vais devoir map mes pixels dans un tableau au lieu de les afficher
//immediatement

void    print_image(t_rgb *img, t_data *data)
{
    int i;
    int j;
    (void)img;

    printf("printing\n");
    i = 0;
    j = 0;
    while (j < HEIGHT)
    {
        while (i < WIDTH)
        {
            mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(img[j * WIDTH + i]));
            i++; 
        }
        i = 0;
        j++;
    }
}

bool is_black(t_rgb pixel)
{
    if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0)
    {
        //print_rgb(pixel); 
        return (true);
    }
    return (false);
}

inline double gaussian_weight(int x, int y, double sigma)
{
    return exp(-((x * x + y * y) / (2 * sigma * sigma)));
}

//ici faire une moyenne (mediane) et compter les pixels noir return l'un ou l'autre en fonction
int total_black(int j, int i, t_rgb *image)
{
    double t = 0;
    int k = -1 * DENOISE_SAMPLE;
    int l;
    double square_side;

    square_side = (1 + (DENOISE_SAMPLE * 2));
    while (k <= 1)
    {
        l = -1 * DENOISE_SAMPLE;
        while (l <= 1)
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
    if ((t / (square_side * square_side)) > BLACK_TRESHHOLD) //the bigger the threshold the less black is ignored
        return (1);
    return (0);
}

t_rgb denoise_pixel(int j, int i, t_rgb *image)//ici faire une moyenne (mediane) et compter les pixels noir return l'un ou l'autre en fonction
{
    int k = -1 * DENOISE_SAMPLE;
    int l;
    int block;
    double total_w = 0.0;

    block = total_black(j, i, image);
    t_rgb blend = (t_rgb){0,0,0};

    while (k <= 1)
    {
        l = -1 * DENOISE_SAMPLE;
        while (l <= 1)
        {
            if (j + k >= 0 && j + k < HEIGHT && i + l >= 0 && i + l < WIDTH)
            {
                if (block && is_black(image[(j + k) * WIDTH + (i + l)]))
                {
                    l++;
                    continue;
                }
                double weight = gaussian_weight(abs(k), abs(l), DENOISE_SIGMA);
                blend = (add_rgbs(blend, mult_rgb_dub(image[(j + k) * WIDTH + (i + l)], weight)));
                total_w += weight;
            }
            l++;
        }
        k++;
    }
    // if (total_w > 0)
    // {
        blend.r /= total_w;
        blend.g /= total_w;
        blend.b /= total_w;
    // }
        return (blend);
}

void    assign_img(t_data *data, t_rgb *denoised)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < HEIGHT)
    {
        while (i < WIDTH)
        {
            data->image[j * WIDTH + i] = denoised[j * WIDTH + i];
            i++;
        }
        i = 0;
        j++;
    }
}

void    denoise_and_render(t_data *data)
{
    t_rgb *denoised;
    int i;
    int j;

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
