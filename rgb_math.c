#include "./includes/miniRT.h"

//inline for faster render and do the color combination and fading calculus here

void    print_rgb(t_rgb rgb)
{
    printf("r : %f\ng : %f\nb : %f\n", rgb.r, rgb.g, rgb.b);
}

inline t_rgb    div_rgb(t_rgb rgb, double a)
{
    return ((t_rgb){rgb.r / a, rgb.g / a, rgb.b / a});
}

inline t_rgb    mult_rgb_dub(t_rgb rgb, double a)
{
    return ((t_rgb){rgb.r * a, rgb.g * a, rgb.b * a});
}

inline t_rgb mult_rgb(t_rgb a, t_rgb b)
{
    return ((t_rgb){a.r * b.r, a.g * b.g, a.b * b.b});
}

inline t_rgb    add_rgbs(t_rgb a, t_rgb b)
{
    //should protect
    return ((t_rgb){a.r + b.r, a.g + b.g, a.b + b.b});
}


double gamma_cor(double color)
{
    if (color > 0)
        return (sqrt(color));
    return (0);
}

double clamp(double color)
{
    if (color <= 0)
        return (0);
    if (color >= 1)
        return (1);
    return (color);
}

int rgb_to_color(t_rgb rgb)
{
    int     color;
    double  r;
    double  g;
    double  b;

    color = 0;

    // if (rgb.r > 1 || rgb.g > 1 || rgb.b > 1)
    //     print_rgb(rgb);
    r = (gamma_cor(clamp(rgb.r)) * 255);
    g = (gamma_cor(clamp(rgb.g)) * 255);
    b = (gamma_cor(clamp(rgb.b)) * 255);


    color |= ((int)r & 0xFF) << 16;
    color |= ((int)g & 0xFF) << 8;
    color |= ((int)b & 0xFF);
    return color;
}