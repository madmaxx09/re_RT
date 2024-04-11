#include "./includes/miniRT.h"

int	int_from_str(const char *str, int min, int max, int *res)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	*res = ft_atoi(str);
	if (*res < min || *res > max)
		return (-1);
	return (0);
}

void    manage_cyl(char **tab, t_data *data)
{
    t_cyl   *new;
    t_cyl   *temp;

    new = gc_malloc(sizeof(t_cyl), data);
    manage_vectors(tab, &new->pos, data, 1);
    manage_vectors(tab, &new->dir, data, 2);
    if (new->dir.x > 1 || new->dir.y > 1 || new->dir.z > 1 
        || new->dir.x < 0 || new->dir.y < 0 || new->dir.z < 0)
        ft_error_exit("Wrong file format", data);
    if (ft_atob(tab[3], 2, 3, &new->diam) == -1 || new->diam <= 0)
        ft_error_exit("Wrong file format", data);
    if (ft_atob(tab[4], 2, 3, &new->height) == -1 || new->height <= 0)   
        ft_error_exit("Wrong file format", data);
    manage_rgb(tab, &new->rgb, data, 5);
    new->dir = norm_vec(new->dir);
    new->next = NULL;
    if (data->cyl == NULL)
        data->cyl = new;
    else
    {
        temp = data->cyl;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}