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


int clamp(int value)
{
    // Clamp the value to the range [0, 255]
    return value < 0 ? 0 : (value > 255 ? 255 : value);
}

int apply_gamma_correction(unsigned char value)
{
    // Apply gamma correction using square root
    return clamp((int)(sqrt((float)value / 255.0f) * 255.0f + 0.5f));
}

// int rgb_to_color(t_rgb rgb)
// {
//     int color = 0;

//     color |= (corrected_r & 0xFF) << 16;
//     color |= (corrected_g & 0xFF) << 8;
//     color |= (corrected_b & 0xFF);

//     return color;
// }


int rgb_to_color(t_rgb rgb)
{
    int color = 0;

    color |= ((int)rgb.r & 0xFF) << 16;
    color |= ((int)rgb.g & 0xFF) << 8;
    color |= ((int)rgb.b & 0xFF);
    return color;
}