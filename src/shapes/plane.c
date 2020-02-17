/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:15:45 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 05:55:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane	*plane_new(t_transform *transform, t_material *material)
{
	t_plane	*new_plane;

	if (!(new_plane = (t_plane*)malloc(sizeof(t_plane))))
		p_error("malloc t_plane");
	new_plane->type = PLANE;
	new_plane->transform.position = transform->position;
	new_plane->transform.rotation = transform->rotation;
	new_plane->material.specular = material->specular;
	new_plane->material.color = material->color;
	return (new_plane);
}

_Bool	plane_intersect(t_inter *inter, t_list_shape *shape_in_list)
{
	t_vec3	temp;
	double	d_dot_n;
	double	t;
	t_plane	*plane;
	t_vec3	normal;

	if (!inter || !shape_in_list)
		error("NULL in plane_intersect");
	plane = (t_plane*)shape_in_list->shape;
	normal = v3_rot_z(v3_rot_y(v3_rot_x((t_vec3){0.0, 0.0, 1.0},
		plane->transform.rotation.x), plane->transform.rotation.y),
		plane->transform.rotation.z);
	if ((d_dot_n = v3_dot(inter->ray.direction, normal)) == 0.0)
		return (FALSE);
	temp = v3_sub(plane->transform.position, inter->ray.origin);
	t = v3_dot(temp, normal) / d_dot_n;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX)
		return (FALSE);
	if (!define_t(t, t, inter, shape_in_list))
		return (TRUE);
	return (FALSE);
}

// t_vec3	get_plane_normal(t_plane *plane, t_ray *ray)
// {
// 	double	d;

// 	d = v3_dot(ray->direction, plane->normal);
// 	if (d < 0)
// 		return (plane->normal);
// 	return (v3_div(plane->normal, -1));
// }
