/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:05:54 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 18:07:57 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere	*sphere_new(t_vec3 center, double radius, int spec)
{
	t_sphere	*new_sphere;

	if (!(new_sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		p_error("malloc t_sphere");
	new_sphere->center = center;
	new_sphere->radius = radius;
	new_sphere->specular = spec;
	new_sphere->shape = SPHERE;
	white(&(new_sphere->color));
	return (new_sphere);
}

_Bool		sphere_intersect(t_inter *inter, t_list_shape *shape_in_list)
{
	t_vec3		new_origin;
	double		coef[3];
	double		discriminant;
	double		t[2];
	t_sphere	*sphere;

	(!inter || !inter->ray || !shape_in_list) ? p_error("null") : 0;
	sphere = (t_sphere*)shape_in_list->content;
	new_origin = v3_sub(inter->ray->origin, sphere->center);
	coef[0] = v3_length_sq(inter->ray->direction);
	coef[1] = 2.0 * v3_dot(inter->ray->direction, new_origin);
	coef[2] = v3_length_sq(new_origin) - sphere->radius * sphere->radius;
	discriminant = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (discriminant < 0.0)
		return (FALSE);
	t[0] = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	if (!define_t(t[0], t[1], inter, shape_in_list))
		return (TRUE);
	return (FALSE);
}

t_vec3		get_sphere_normal(t_sphere *sphere, t_vec3 hit_point)
{
	t_vec3	normal;

	normal = v3_sub(hit_point, sphere->center);
	normal = v3_norm(normal);
	return (normal);
}
