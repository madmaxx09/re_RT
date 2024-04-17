/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdor <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:47:54 by mdor              #+#    #+#             */
/*   Updated: 2024/04/17 19:47:56 by mdor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

//vecteur normal = perpendiculaire a ma surface a un point donné
//on fait un vec normal dirigé vers l'ext donc pt - pos
inline t_vec   normal_sp(t_sphere *sph, t_vec point)
{
    return (div_vec(dif_vec(point, sph->pos), sph->diam / 2));
}

inline double  len_vec(t_vec vec)
{
    return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z *vec.z));
}

inline t_vec	vec_by_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x * b.x, a.y * b.y, a.z * b.z});
}

inline t_vec   dif_vec(t_vec a, t_vec b)
{
    return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z}); 
}

inline t_vec    div_vec(t_vec a, double b)
{
    return ((t_vec){a.x / b, a.y / b, a.z / b});
}

inline t_vec    mult_vec(t_vec a, double b)
{
    return ((t_vec){a.x * b, a.y * b, a.z * b});
}

inline t_vec    add_vec(t_vec a, t_vec b)
{
    return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

//distance = difference entre 2 vec puis longueur de celui ci etant la racine de produit le signe
//na pas de valeur 
inline double   dist(t_vec  src, t_vec dest)
{
    return (len_vec(dif_vec(src, dest)));
}

inline t_vec   norm_vec(t_vec vec)
{
    double len;

    len = len_vec(vec);
    if (len == 0)
    {
        return ((t_vec){0,0,0});    
    }
    return ((t_vec){vec.x / len, vec.y / len, vec.z / len});
}

inline double dot_prod(t_vec a, t_vec b)
{
    return ((double)a.x * b.x + a.y * b.y + a.z * b.z);
}

void    print_vec(t_vec a)
{
    printf("x : %f\n", a.x);
    printf("y : %f\n", a.y);
    printf("z : %f\n", a.z);
}

inline t_vec lin_comb(double a, t_vec i, double b, t_vec j)
{
    return (add_vec(mult_vec(i, a), mult_vec(j, b)));
}
