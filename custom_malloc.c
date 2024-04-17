/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   custom_malloc.c									:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mdor <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/01/06 10:24:53 by mdor			  #+#	#+#			      */
/*   Updated: 2024/04/17 19:42:55 by mdor             ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include <stdio.h>
#include "./includes/miniRT.h"

int	update_free_list(t_malloc **head, void *adress, t_data *data)
{
	t_malloc	*newnode;
	t_malloc	*temp;

	temp = NULL;
	newnode = malloc(sizeof(t_malloc));
	if (newnode == NULL)
	{
		ft_putstr_fd("malloc failure\n", 2);
		data->error_trigger = 1;
		return (1);
	}
	newnode->adress = adress;
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (0);
}

void	free_strings(t_malloc *node)
{
	t_malloc	*temp;
	t_malloc	*next;

	temp = NULL;
	next = NULL;
	temp = node;
	while (temp)
	{
		if (temp->adress)
			free(temp->adress);
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	free_custom_alloc(t_data *data)
{
	if (data->head)
		free_strings(data->head);
	data->head = NULL;
}

void	*gc_malloc(size_t required_memory, t_data *data)
{
	void	*memory;

	memory = malloc(required_memory);
	if (!memory)
	{
		ft_putstr_fd("malloc failure\n", 2);
		data->error_trigger = 1;
	}
	if (update_free_list(&data->head, memory, data))
		return (NULL);
	return (memory);
}
