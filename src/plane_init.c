/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:15:45 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 17:57:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane	*plane_new(t_vec3 position, t_vec3 normal, int spec)
{
	t_plane	*new_plane;

	if (!(new_plane = (t_plane*)malloc(sizeof(t_plane))))
		p_error("malloc t_plane");
	new_plane->position = position;
	new_plane->normal = v3_norm(normal);
	new_plane->specular = spec;
	new_plane->shape = PLANE;
	white(&new_plane->color);
	return (new_plane);
}

_Bool	plane_intersect(t_inter *inter, t_list_shape *shape_in_list)
{
	t_vec3	temp;
	double	d_dot_n;
	double	t;
	t_plane	*plane;

	if (!inter || !inter->ray || !shape_in_list)
		error("NULL in plane_intersect");
	plane = (t_plane*)shape_in_list->content;
	if ((d_dot_n = v3_dot(inter->ray->direction, plane->normal)) == 0.0)
		return (FALSE);
	temp = v3_sub(plane->position, inter->ray->origin);
	t = v3_dot(temp, plane->normal) / d_dot_n;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX)
		return (FALSE);
	if (!define_t(t, t, inter, shape_in_list))
		return (TRUE);
	return (FALSE);
}

t_vec3	get_plane_normal(t_plane *plane, t_ray *ray)
{
	double	d;

	d = v3_dot(ray->direction, plane->normal);
	if (d < 0)
		return (plane->normal);
	return (v3_div(plane->normal, -1));
}
