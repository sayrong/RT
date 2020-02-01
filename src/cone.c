/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:01:15 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 16:50:32 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		define_t(double t1, double t2, t_inter *inter,
					t_list_shape *shape_in_list)
{
	double	tmp;

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

t_cone	*cone_new(t_vec3 position, t_vec3 direction, double angle, int spec)
{
	t_cone	*new_cone;

	if (!(new_cone = (t_cone*)malloc(sizeof(t_cone))))
		p_error("malloc t_cone");
	new_cone->position = position;
	new_cone->dir = v3_norm(direction);
	new_cone->angle = angle;
	new_cone->specular = spec;
	new_cone->shape = CONE;
	white(&new_cone->color);
	return (new_cone);
}

double	degrees_to_rad(double angle_in_degrees)
{
	return ((angle_in_degrees * M_PI / 180.0) / 2);
}

/*
**	a   = D|D - (1+k*k)*(D|V)^2
**	b/2 = D|X - (1+k*k)*(D|V)*(X|V)
**	c   = X|X - (1+k*k)*(X|V)^2
**	X equals O-C.
*/

_Bool	cone_intersect(t_inter *inter, t_list_shape *shape_in_list)
{
	double		abc[3];
	double		t[2];
	t_vec3		x;
	t_cone		*cone;
	double		k_and_discr[2];

	cone = ((t_cone*)shape_in_list->content);
	x = v3_sub(inter->ray->origin, cone->position);
	k_and_discr[0] = 1 +
			tan(degrees_to_rad(cone->angle)) * tan(degrees_to_rad(cone->angle));
	abc[0] = v3_length_sq(inter->ray->direction) -
			k_and_discr[0] * pow(v3_dot(inter->ray->direction, cone->dir), 2);
	abc[1] = 2 * (v3_dot(inter->ray->direction, x) -
				k_and_discr[0] * v3_dot(inter->ray->direction, cone->dir) *
					v3_dot(x, cone->dir));
	abc[2] = v3_length_sq(x) - k_and_discr[0] * pow(v3_dot(x, cone->dir), 2);
	k_and_discr[1] = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (k_and_discr[1] < 0)
		return (FALSE);
	t[0] = (-abc[1] + sqrt(k_and_discr[1])) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(k_and_discr[1])) / (2 * abc[0]);
	if (!define_t(t[0], t[1], inter, shape_in_list))
		return (TRUE);
	return (FALSE);
}

t_vec3	get_cone_normal(t_cone *cone, t_ray *ray, t_vec3 hit_point, double t)
{
	double	k;
	double	m;
	t_vec3	tmp[8];
	t_vec3	normal;

	k = tan(degrees_to_rad(cone->angle));
	tmp[0] = v3_sub(ray->origin, cone->position);
	m = v3_dot(ray->direction, cone->dir) * t + v3_dot(tmp[0], cone->dir);
	tmp[1] = v3_sub(hit_point, cone->position);
	tmp[2] = v3_scale(cone->dir, m);
	tmp[3] = v3_sub(tmp[1], tmp[2]);
	tmp[4] = v3_scale(cone->dir, m);
	tmp[5] = v3_scale(tmp[4], k);
	tmp[6] = v3_scale(tmp[5], k);
	tmp[7] = v3_sub(tmp[3], tmp[6]);
	normal = v3_norm(tmp[7]);
	return (normal);
}
