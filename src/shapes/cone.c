/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:01:15 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 05:54:11 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		define_t(float t1, float t2, t_inter *inter,
					t_list_shape *shape_in_list)
{
	float	tmp;

	tmp = -1;
	if (t1 > RAY_T_MIN && (t1 <= t2 || t2 <= 0))
		tmp = t1;
	if (t2 > RAY_T_MIN && (t2 < t1 || t1 <= 0))
		tmp = t2;
	if (tmp == -1)
		return (1);
	if (tmp < inter->t)
	{
		inter->t = tmp;
		inter->shape = shape_in_list;
		return (0);
	}
	return (1);
}

t_cone	*cone_new(t_transform *transform, t_material *material,
						float angle)
{
	t_cone	*new_cone;

	if (!(new_cone = (t_cone*)malloc(sizeof(t_cone))))
		p_error("malloc t_cone");
	new_cone->type = CONE;
	new_cone->transform.position = transform->position;
	new_cone->transform.rotation = transform->rotation;
	new_cone->angle = angle;
	new_cone->material.specular = material->specular;
	new_cone->material.color = material->color;
	return (new_cone);
}

float	degrees_to_rad(float angle_in_degrees)
{
	return ((angle_in_degrees * M_PI / 180.0) / 2);
}

/*
**	a   = D|D - (1+k*k)*(D|V)^2
**	b/2 = D|X - (1+k*k)*(D|V)*(X|V)
**	c   = X|X - (1+k*k)*(X|V)^2
**	X equals O-C.
*/

_Bool	cone_intersect(t_inter *inter, t_list_shape *shape_in_list,
					t_cone *cone)
{
	float		abc[3];
	float		t[2];
	t_vec3		x_axis[2];
	float		k_and_discr[2];

	cone = ((t_cone*)shape_in_list->shape);
	x_axis[0] = v3_sub(inter->ray.origin, cone->transform.position);
	x_axis[1] = v3_rot_z(v3_rot_y(v3_rot_x((t_vec3){0.0, 0.0, 1.0},
		cone->transform.rotation.x), cone->transform.rotation.y),
		cone->transform.rotation.z);
	k_and_discr[0] = 1 +
			tan(degrees_to_rad(cone->angle)) * tan(degrees_to_rad(cone->angle));
	abc[0] = v3_length_sq(inter->ray.direction) -
		k_and_discr[0] * pow(v3_dot(inter->ray.direction, x_axis[1]), 2);
	abc[1] = 2 * (v3_dot(inter->ray.direction, x_axis[0]) -
		k_and_discr[0] * v3_dot(inter->ray.direction, x_axis[1]) *
			v3_dot(x_axis[0], x_axis[1]));
	abc[2] = v3_length_sq(x_axis[0]) -
		k_and_discr[0] * pow(v3_dot(x_axis[0], x_axis[1]), 2);
	k_and_discr[1] = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (k_and_discr[1] < 0)
		return (FALSE);
	t[0] = (-abc[1] + sqrt(k_and_discr[1])) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(k_and_discr[1])) / (2 * abc[0]);
	return (!define_t(t[0], t[1], inter, shape_in_list));
}

// t_vec3	get_cone_normal(t_cone *cone, t_ray *ray, t_vec3 hit_point, float t)
// {
// 	float	k;
// 	float	m;
// 	t_vec3	tmp[8];
// 	t_vec3	normal;

// 	k = tan(degrees_to_rad(cone->angle));
// 	tmp[0] = v3_sub(ray->origin, cone->position);
// 	m = v3_dot(ray->direction, cone->dir) * t + v3_dot(tmp[0], cone->dir);
// 	tmp[1] = v3_sub(hit_point, cone->position);
// 	tmp[2] = v3_scale(cone->dir, m);
// 	tmp[3] = v3_sub(tmp[1], tmp[2]);
// 	tmp[4] = v3_scale(cone->dir, m);
// 	tmp[5] = v3_scale(tmp[4], k);
// 	tmp[6] = v3_scale(tmp[5], k);
// 	tmp[7] = v3_sub(tmp[3], tmp[6]);
// 	normal = v3_norm(tmp[7]);
// 	return (normal);
// }
