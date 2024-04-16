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


                // if (blend.r > 1 || blend.g > 1 || blend.b > 1)
                // {
                //     printf("new sample is : %f\n", sample);
                //     print_rgb(image[(j + k) * WIDTH + (i + l)]);
                //     printf("between pix up blend down\n");
                //     print_rgb(blend);
                // }

inline double gaussian_weight(int x, int y, double sigma)
{
    return exp(-((x * x + y * y) / (2 * sigma * sigma)));
}

t_rgb are_they_black(int j, int i, t_rgb *image)//ici faire une moyenne (mediane) et compter les pixels noir return l'un ou l'autre en fonction
{
    int t = 0;
    int k = -1 * DENOISE_SAMPLE;
    int l;
    double total_w = 0.0;

    //double sample = (double)(1 / ((1 + (DENOISE_SAMPLE * 2)) * (1 + (DENOISE_SAMPLE * 2))));
    //printf("sample : %f\n", sample);
    t_rgb blend = (t_rgb){0,0,0};

    while (k <= 1)
    {
        l = -1 * DENOISE_SAMPLE;
        while (l <= 1)
        {
            if (j + k >= 0 && j + k < HEIGHT && i + l >= 0 && i + l < WIDTH)
            {
                double weight = gaussian_weight(abs(k), abs(l), DENOISE_SIGMA);
                blend = (add_rgbs(blend, mult_rgb_dub(image[(j + k) * WIDTH + (i + l)], weight)));
                total_w += weight;
                if (is_black(image[(j + k) * WIDTH + (i + l)]))
                    t++;
            }
            l++;
        }
        k++;
    }
    if (total_w > 0)
    {
        blend.r /= total_w;
        blend.g /= total_w;
        blend.b /= total_w;
    }
    if (t > (7 * DENOISE_SAMPLE))
        return ((t_rgb){0,0,0});
    else
        return (blend);
}

    //blend = (t_rgb){1,1,1};
    //printf("tet\n");
    // t_rgb up = *image[(j - 1) * WIDTH + i];
    // t_rgb down = *image[(j + 1) * WIDTH + i];
    // t_rgb left = *image[j * WIDTH + (i - 1)];
    // t_rgb right = *image[j * WIDTH + (i + 1)];
    
    // t_rgb up_left = *image[(j - 1) * WIDTH + (i - 1)];
    // t_rgb up_right = *image[(j - 1) * WIDTH + (i + 1)];
    // t_rgb down_left = *image[(j + 1) * WIDTH + (i - 1)];
    // t_rgb down_right = *image[(j + 1) * WIDTH + (i + 1)];

t_rgb   denoise_pixel(int j, int i, t_rgb *image)//ici que le magie doit opérer
{
    //printf("t\n");
    //t_rgb center = image[j * WIDTH + i];
    //t_rgb blend;
    //blend = (t_rgb){0,0,0};

    //on va traiter r g et b independemment;
    //ok test si 8 pixels adjacents sont noir alors pixel central est noir 
    // if (are_they_black(j, i, image, &blend, 1))//7 arbitrairement mais on va changer en fonction de SAMPLE plus tard
    // {
    //     //print_rgb(center);
    //     return ((t_rgb){0,0,0});
    // }
    return (are_they_black(j, i, image));
    //return (blend);
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

void    denoise_and_render(t_data *data, t_rgb *image)
{
    (void)image;
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
            //mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(denoise_pixel(j, i, data->image)));
            denoised[j * WIDTH + i] = denoise_pixel(j, i, data->image);
            i++; 
        }
        i = 0;
        j++;
    }
    assign_img(data, denoised);
    //data->image = denoised;
    free(denoised);
    //print_image(data->image, data);
}