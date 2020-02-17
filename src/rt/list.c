/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:52:57 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 06:18:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list_shape	*new_shape_list(void *shape, t_shape_type type)
{
	t_list_shape	*new;

	if (!(new = (t_list_shape*)malloc(sizeof(t_list_shape))))
		p_error("malloc t_list_shape");
	new->type = type;
	new->shape = shape;
	new->marker = FALSE;
	new->next = NULL;
	return (new);
}

t_list_shape	*add_new_shape(t_list_shape *list, void *shape,
								t_shape_type type, int *counter)
{
	t_list_shape	*tmp;

	tmp = list;
	list = new_shape_list(shape, type);
	list->next = tmp;
	++(*counter);
	return (list);
}

t_list_light	*new_light_list(t_light *light, t_light_type type)
{
	t_list_light	*new;

	if (!(new = (t_list_light*)malloc(sizeof(t_list_light))))
		p_error("malloc t_list_light");
	new->type = type;
	new->light = light;
	new->next = NULL;
	return (new);
}

t_list_light	*add_new_light(t_list_light *list, t_light *light,
							t_light_type type, int *counter)
{
	t_list_light	*tmp;

	tmp = list;
	list = new_light_list(light, type);
	list->next = tmp;
	++(*counter);
	return (list);
}
