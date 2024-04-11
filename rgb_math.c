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

inline  t_rgb   color_blend(double t, t_rgb a, t_rgb b)
{
    return ((t_rgb){
            (1.0 - t) * a.r + t * b.r,
            (1.0 - t) * a.g + t * b.g,
            (1.0 - t) * a.b + t * b.b
    });
}

double gamma_cor(double color)
{
    if (color > 0)
        return (sqrt(color));
    return (0);
}

double clamp(double color, double min, double max)
{
    if (color < min)
        return (min);
    if (color > max)
        return (max);
    return (color);
}

int rgb_to_color(t_rgb rgb)
{
    int     color;

    color = 0;
    if (rgb.r != rgb.r)
        rgb.r = 0;
    if (rgb.g != rgb.g)
        rgb.g = 0;
    if (rgb.b != rgb.b)
        rgb.b = 0;

    rgb.r = gamma_cor(clamp(rgb.r, 0.0, 0.999)) * 256;
    rgb.g = gamma_cor(clamp(rgb.g, 0.0, 0.999)) * 256;
    rgb.b = gamma_cor(clamp(rgb.b, 0.0, 0.999)) * 256;

    color |= ((int)rgb.r & 0xFF) << 16;
    color |= ((int)rgb.g & 0xFF) << 8;
    color |= ((int)rgb.b & 0xFF);
    return color;
}