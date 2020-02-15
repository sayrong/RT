/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:57:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 13:02:45 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	white(t_color *color)
{
	color->r = 255;
	color->g = 255;
	color->b = 255;
}

int		get_color(t_color *c, double light)
{
	int	new_red;
	int	new_green;
	int	new_blue;

	new_red = c->r * light;
	new_green = c->g * light;
	new_blue = c->b * light;
	return (new_red << 16 | new_green << 8 | new_blue);
}

t_color	*get_color_from_list(t_list_shape *list)
{
	if (list->shape == SPHERE)
		return (&(((t_sphere*)list->content)->color));
	else if (list->shape == PLANE)
		return (&(((t_plane*)list->content)->color));
	else if (list->shape == CONE)
		return (&(((t_cone*)list->content)->color));
	else if (list->shape == CYLINDER)
		return (&(((t_cylinder*)list->content)->color));
	return (NULL);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}
