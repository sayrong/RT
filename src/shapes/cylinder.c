/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:10:14 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/10/13 16:54:05 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cylinder	*cylinder_new(t_vec3 position, t_vec3 direction, double r, int spec)
{
	t_cylinder	*new_cylinder;

	if (!(new_cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		p_error("malloc t_cylinder");
	new_cylinder->position = position;
	new_cylinder->dir = v3_norm(direction);
	new_cylinder->radius = r;
	new_cylinder->specular = spec;
	new_cylinder->shape = CYLINDER;
	white(&new_cylinder->color);
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
	t_cylinder	*cylinder;

	cylinder = ((t_cylinder*)shape_in_list->content);
	x = v3_sub(inter->ray->origin, cylinder->position);
	abcd[0] = v3_dot(inter->ray->direction, inter->ray->direction)
		- pow(v3_dot(inter->ray->direction, cylinder->dir), 2);
	abcd[1] = 2 * (v3_dot(inter->ray->direction, x) -
				(v3_dot(inter->ray->direction, cylinder->dir) *
					v3_dot(x, cylinder->dir)));
	abcd[2] = v3_dot(x, x) - pow(v3_dot(x, cylinder->dir), 2) -
				cylinder->radius * cylinder->radius;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return (FALSE);
	t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
	if (!define_t(t[0], t[1], inter, shape_in_list))
		return (TRUE);
	return (FALSE);
}

t_vec3		get_cyl_normal(t_cylinder *cyl, t_ray *ray, t_vec3 hit_point,
							double t)
{
	double	m;
	t_vec3	x;
	t_vec3	tmp[3];
	t_vec3	normal;

	x = v3_sub(ray->origin, cyl->position);
	m = v3_dot(ray->direction, cyl->dir) * t + v3_dot(x, cyl->dir);
	tmp[0] = v3_sub(hit_point, cyl->position);
	tmp[1] = v3_scale(cyl->dir, m);
	tmp[2] = v3_sub(tmp[0], tmp[1]);
	normal = v3_norm(tmp[2]);
	return (normal);
}
