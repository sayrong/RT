/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:52:57 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 01:55:47 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list_shape	*new_shape_list(void *content, t_shape_type type)
{
	t_list_shape	*new;

	if (!(new = (t_list_shape*)malloc(sizeof(t_list_shape))))
		p_error("malloc t_list_shape");
	new->content = content;
	new->shape = type;
	new->next = NULL;
	return (new);
}

t_list_shape	*add_new_shape(t_list_shape *list, void *content,
								t_shape_type type)
{
	t_list_shape	*tmp;

	tmp = list;
	if (list == NULL)
		list = new_shape_list(content, type);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_shape_list(content, type);
	}
	return (list);
}

t_list_light	*new_light_list(t_light *light, t_light_type type)
{
	t_list_light	*new;

	if (!(new = (t_list_light*)malloc(sizeof(t_list_light))))
		p_error("malloc t_list_light");
	new->light = light;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_list_light	*add_new_light(t_list_light *list, t_light *light,
							t_light_type type)
{
	t_list_light	*tmp;

	tmp = list;
	if (list == NULL)
		list = new_light_list(light, type);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_light_list(light, type);
	}
	return (list);
}
