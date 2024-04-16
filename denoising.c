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
    i = 1;
    j = 1;
    while (j < HEIGHT)
    {
        while (i < WIDTH)
        {
            // if (data->image[j * WIDTH + i].r > 0 || data->image[j * WIDTH + i].g > 0 || data->image[j * WIDTH + i].b > 0)
            //     print_rgb(data->image[j * WIDTH + i]);
            //mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(data->image[j * WIDTH + i]));
            mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(img[j * WIDTH + i]));
            i++; 
        }
        i = 1;
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

int are_they_black(int j, int i, t_rgb *image, t_rgb *blend)//ici faire une moyenne (mediane) et compter les pixels noir return l'un ou l'autre en fonction
{
    int t = 0;
    int k = -1;
    int l;
    (void)blend;

    while (k <= 1)
    {
        l = -1;
        while (l <= 1)
        {
            // Check if the pixel is within image boundaries
            if (j + k >= 0 && j + k < HEIGHT && i + l >= 0 && i + l < WIDTH)
            {
                if ((k != 0 && l != 0) && is_black(image[(j + k) * WIDTH + (i + l)]))
                    t++;
            }
            l++;
        }
        k++;
    }
    return (t > 7) ? 1 : 0;
}

// int are_they_black(int j, int i, t_rgb *image)
// {
//     int t = 0;

//     // Check top pixel
//     if (j - 1 >= 0 && is_black(image[(j - 1) * WIDTH + i])) {
//         t++;
//     }
//     // Check bottom pixel
//     if (j + 1 < HEIGHT && is_black(image[(j + 1) * WIDTH + i])) {
//         t++;
//     }
//     // Check left pixel
//     if (i - 1 >= 0 && is_black(image[j * WIDTH + (i - 1)])) {
//         t++;
//     }
//     // Check right pixel
//     if (i + 1 < WIDTH && is_black(image[j * WIDTH + (i + 1)])) {
//         t++;
//     }

//     // If all four surrounding pixels are black, return true
//     return (t == 4) ? 1 : 0;
// }

t_rgb   denoise_pixel(int j, int i, t_rgb *image)//ici que le magie doit opérer
{
    //printf("t\n");
    t_rgb center = image[j * WIDTH + i];
    t_rgb blend;
    blend = (t_rgb){1,1,1};
    //printf("tet\n");
    // t_rgb up = *image[(j - 1) * WIDTH + i];
    // t_rgb down = *image[(j + 1) * WIDTH + i];
    // t_rgb left = *image[j * WIDTH + (i - 1)];
    // t_rgb right = *image[j * WIDTH + (i + 1)];
    
    // t_rgb up_left = *image[(j - 1) * WIDTH + (i - 1)];
    // t_rgb up_right = *image[(j - 1) * WIDTH + (i + 1)];
    // t_rgb down_left = *image[(j + 1) * WIDTH + (i - 1)];
    // t_rgb down_right = *image[(j + 1) * WIDTH + (i + 1)];

    //on va traiter r g et b independemment;
    //ok test si 8 pixels adjacents sont noir alors pixel central est noir 
    if (are_they_black(j, i, image, &blend))//7 arbitrairement mais on va changer en fonction de SAMPLE plus tard
    {
        //print_rgb(center);
        return ((t_rgb){0,0,0});
    }
    
    return (center);
}

void print_prog(int process)
{
    int progress = (int)(((float)process / TOTAL) * 100);
    int bar_length = progress / 2;

    printf("\rDenoising : [");
    for (int k = 0; k < bar_length; k++) {
        printf("#");
    }
    for (int k = bar_length; k < 50; k++) {
        printf(" ");
    }
    printf("] %d%%", progress);
}

void    denoise_and_render(t_data *data, t_rgb *image)
{
    t_rgb *denoised;
    (void)image;
    int i;
    int j;
    //int process = 0;

    i = 1;
    j = 1;

    printf("test\n");
    denoised = malloc(sizeof(t_rgb) * WIDTH * HEIGHT);
    ft_bzero(denoised, sizeof(t_rgb) * WIDTH * HEIGHT);
    while (j < HEIGHT)
    {
        while (i < WIDTH)
        {
            //process++;
            mlx_pixel_put(data->mlx, data->wind, i, j, rgb_to_color(denoise_pixel(j, i, data->image)));
            //denoised[j * WIDTH + i] = denoise_pixel(j, i, data->image);
            //print_prog(process);
            i++; 
        }
        i = 0;
        j++;
    }
    //print_image(denoised, data);
}