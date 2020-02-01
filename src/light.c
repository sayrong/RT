/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:53:12 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 23:30:15 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	compute_specular(t_vec3 normal_to_intersect, t_vec3 light_vector,
						t_inter *inter, int object_specular)
{
	double	percent;
	double	angle;
	t_vec3	to_camera_vector;
	t_vec3	light;

	percent = 0;
	to_camera_vector = v3_scale(inter->ray->direction, -1);
	light = v3_scale(normal_to_intersect, 2);
	light = v3_scale(light, v3_dot(normal_to_intersect, light_vector));
	light = v3_sub(light, light_vector);
	angle = v3_dot(light, to_camera_vector);
	if (angle > 0)
		percent = pow(angle / (v3_length(light) * v3_length(to_camera_vector)),
					object_specular);
	return (percent);
}

t_vec3	get_intersection_point(t_inter *inter)
{
	t_vec3	intersection_point;

	intersection_point = v3_scale(inter->ray->direction, inter->t);
	intersection_point = v3_add(inter->ray->origin, intersection_point);
	return (intersection_point);
}

int		is_in_shadow(t_list_light *light, t_list_shape *scene,
				t_vec3 intersection_point)
{
	t_inter			inter;
	t_vec3			dir;
	t_ray			ray;
	double			dist;
	t_list_shape	*obj;

	dist = v3_length(v3_sub(light->light->position, intersection_point));
	dir = v3_sub(intersection_point, light->light->position);
	dir = v3_norm(dir);
	ray.origin = light->light->position;
	ray.direction = dir;
	ray.t_max = RAY_T_MAX;
	inter_new_ray(&inter, &ray);
	obj = scene;
	while (obj != NULL)
	{
		shape_intersect(&inter, obj);
		obj = obj->next;
	}
	if (inter.t < dist - 0.0000001)
		return (1);
	return (0);
}

double	diffuse_light(t_list_light *light, t_inter *inter,
					t_vec3 intersection_point)
{
	double	res;
	double	angle;
	t_vec3	light_vector;
	t_vec3	normal_to_intersect;

	res = 0;
	normal_to_intersect = get_normal(inter);
	light_vector = v3_sub(light->light->position, intersection_point);
	angle = v3_dot(normal_to_intersect, light_vector);
	if (angle > 0)
	{
		res += ((light->light->intensity * angle) /
				(v3_length(normal_to_intersect) * v3_length(light_vector)));
	}
	if (get_specular(inter) > 0)
	{
		angle = compute_specular(normal_to_intersect, light_vector, inter,
								get_specular(inter));
		res += (light->light->intensity * angle);
	}
	return (res);
}

double	compute_light(t_inter *inter, t_list_shape *scene, t_list_light *lights)
{
	double			res;
	t_list_light	*light;
	t_vec3			intersection;

	res = 0;
	light = lights;
	intersection = get_intersection_point(inter);
	while (light != NULL)
	{
		if (light->type == AMBIENT)
			res += light->light->intensity;
		else if (light->type == POINT)
			if (!is_in_shadow(light, scene, intersection))
				res += diffuse_light(light, inter, intersection);
		light = light->next;
	}
	if (res > 1)
		res = 1;
	return (res);
}
