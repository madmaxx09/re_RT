/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   mlx_press.c										:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+	   	  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/04/17 19:46:02 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:46:04 by mdor			 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "./includes/miniRT.h"

int	presskey(int key, t_data *data)
{
	if (key == 53)
	{
		ft_error_exit("Program closed", data);
		exit(1);
	}
	return (0);
}
