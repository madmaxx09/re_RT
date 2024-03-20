#include "./includes/miniRT.h"

//inline for faster render and do the color combination and fading calculus here

inline t_rgb    mult_rgb_dub(t_rgb rgb, double a)
{
    return ((t_rgb){rgb.r * a, rgb.g * a, rgb.b * a});
}

inline t_rgb    add_rgbs(t_rgb a, t_rgb b)
{
    //should protect
    return ((t_rgb){a.r + b.r, a.g + b.g, a.b + b.b});
}

int rgb_to_color(t_rgb rgb)
{
    int color = 0;

    color |= ((int)rgb.r & 0xFF) << 16;
    color |= ((int)rgb.g & 0xFF) << 8;
    color |= ((int)rgb.b & 0xFF);
    return color;
}