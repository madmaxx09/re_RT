#include "./includes/miniRT.h"

int presskey(int key, t_data *data)
{
    print_args(data);
    if (key == 53)
    {
        ft_error_exit("Program closed", data);
        print_args(data);
        exit(1);
    }
    //coder le comportement pour deplacer les objets et la lumiere
    //avec un update des calculs de l'image pour chaque cas
    



    return (0);
}