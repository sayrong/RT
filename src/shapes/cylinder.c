/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:10:14 by balvyn-s          #+#    #+#             */
/*   Updated: 2020/02/17 05:54:40 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cylinder	*cylinder_new(t_transform *transform, t_material *material,
						float radius)
{
	t_cylinder	*new_cylinder;

	if (!(new_cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		p_error("malloc t_cylinder");
	new_cylinder->type = CYLINDER;
	new_cylinder->transform.position = transform->position;
	new_cylinder->transform.rotation = transform->rotation;
	new_cylinder->radius = radius;
	new_cylinder->material.specular = material->specular;
	new_cylinder->material.color = material->color;
	return (new_cylinder);
}

/*
**	a = D|D - (D|V)^2
**	b/2 = D|X - (D|V)*(X|V)
**	c = X|X - (X|V)^2 - r*r
*/

_Bool		cylinder_intersect(t_inter *inter, t_list_shape *shape_in_list)
{
	double		abcd[4];
	double		t[2];
	t_vec3		x;
	t_vec3		axis;
	t_cylinder	*cylinder;

	cylinder = ((t_cylinder*)shape_in_list->shape);
	x = v3_sub(inter->ray.origin, cylinder->transform.position);
	axis = v3_rot_z(v3_rot_y(v3_rot_x((t_vec3){0.0, 0.0, 1.0},
		cylinder->transform.rotation.x), cylinder->transform.rotation.y),
		cylinder->transform.rotation.z);
	abcd[0] = v3_dot(inter->ray.direction, inter->ray.direction)
		- pow(v3_dot(inter->ray.direction, axis), 2);
	abcd[1] = 2 * (v3_dot(inter->ray.direction, x) -
				(v3_dot(inter->ray.direction, axis) *
					v3_dot(x, axis)));
	abcd[2] = v3_dot(x, x) - pow(v3_dot(x, axis), 2) -
				cylinder->radius * cylinder->radius;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return (FALSE);
	t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
	return (!define_t(t[0], t[1], inter, shape_in_list));
}

// t_vec3		get_cyl_normal(t_cylinder *cyl, t_ray *ray, t_vec3 hit_point,
// 							double t)
// {
// 	double	m;
// 	t_vec3	x;
// 	t_vec3	tmp[3];
// 	t_vec3	normal;

// 	x = v3_sub(ray->origin, cyl->position);
// 	m = v3_dot(ray->direction, cyl->dir) * t + v3_dot(x, cyl->dir);
// 	tmp[0] = v3_sub(hit_point, cyl->position);
// 	tmp[1] = v3_scale(cyl->dir, m);
// 	tmp[2] = v3_sub(tmp[0], tmp[1]);
// 	normal = v3_norm(tmp[2]);
// 	return (normal);
// }
