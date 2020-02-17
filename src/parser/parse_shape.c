/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:56:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 06:16:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_plane(t_rt *rt, char **split, int line_num)
{
	t_transform	transform;
	t_material	material;
	t_plane		*plane;

	if (rt->cnt.plane == MAX_CNT_SHAPES)
		parse_error("Max count of planes", line_num);
	if (!str_to_v3(&transform.position, split[1]))
		parse_error("Invalid param: position point of the plane", line_num);
	if (!str_to_v3(&transform.rotation, split[2]))
		parse_error("Invalid param: rotation vector of the plane", line_num);
	if (!str_to_rgb(&material.color, split[3]))
		parse_error("Invalid param: color value of the plane", line_num);
	if (!is_valid_float(split[4]))
		parse_error("Invalid param: specular value of the plane", line_num);
	material.specular = str_to_float(split[4]);
	if (material.specular < 0 || material.specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	plane = plane_new(&transform, &material);
	rt->shapes = add_new_shape(rt->shapes, plane, PLANE, &rt->cnt.plane);
}

static void	parse_sphere(t_rt *rt, char **split, int line_num)
{
	t_transform	transform;
	t_material	material;
	float		radius;
	t_sphere	*sphere;

	if (rt->cnt.sphere == MAX_CNT_SHAPES)
		parse_error("Max count of planes", line_num);
	if (!str_to_v3(&transform.position, split[1]))
		parse_error("Invalid param: position point of the sphere", line_num);
	if (!str_to_v3(&transform.rotation, split[2]))
		parse_error("Invalid param: rotation vector of the sphere", line_num);
	if (!is_valid_float(split[3]))
		parse_error("Invalid param: radius value of the sphere", line_num);
	radius = str_to_float(split[3]);
	if (radius <= 0)
		parse_error("Radius for the sphere must be positive", line_num);
	if (!str_to_rgb(&material.color, split[4]))
		parse_error("Invalid param: color value of the sphere", line_num);
	if (!is_valid_float(split[5]))
		parse_error("Invalid param: specular value of the sphere", line_num);
	material.specular = str_to_float(split[4]);
	if (material.specular < 0 || material.specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	sphere = sphere_new(&transform, &material, radius);
	rt->shapes = add_new_shape(rt->shapes, sphere, SPHERE, &rt->cnt.sphere);
}

static void	parse_cylinder(t_rt *rt, char **split, int line_num)
{
	t_transform	transform;
	t_material	material;
	double		radius;
	t_cylinder	*cylinder;

	if (rt->cnt.cylinder == MAX_CNT_SHAPES)
		parse_error("Max count of cylinder", line_num);
	if (!str_to_v3(&transform.position, split[1]))
		parse_error("Invalid param: position point of the cylinder", line_num);
	if (!str_to_v3(&transform.rotation, split[2]))
		parse_error("Invalid param: rotation vector of the cylinder", line_num);
	if (!is_valid_float(split[3]))
		parse_error("Invalid param: radius value of the cylinder", line_num);
	radius = str_to_float(split[3]);
	(radius <= 0) ? parse_error("Radius must be positive", line_num) : 0;
	if (!str_to_rgb(&material.color, split[4]))
		parse_error("Invalid param: color value of the cylinder", line_num);
	if (!is_valid_float(split[5]))
		parse_error("Invalid param: specular value of the cylinder", line_num);
	material.specular = str_to_float(split[4]);
	if (material.specular < 0 || material.specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	cylinder = cylinder_new(&transform, &material, radius);
	rt->shapes = add_new_shape(rt->shapes, cylinder, CYLINDER,
								&rt->cnt.cylinder);
}

static void	parse_cone(t_rt *rt, char **split, int line_num)
{
	t_transform	transform;
	t_material	material;
	double		angle;
	t_cone		*cone;

	if (rt->cnt.cone == MAX_CNT_SHAPES)
		parse_error("Max count of cylinder", line_num);
	if (!str_to_v3(&transform.position, split[1]))
		parse_error("Invalid param: position point of the cone", line_num);
	if (!str_to_v3(&transform.rotation, split[2]))
		parse_error("Invalid param: rotation vector of the cone", line_num);
	if (!is_valid_float(split[3]))
		parse_error("Invalid param: angle value of the cone", line_num);
	angle = str_to_float(split[3]);
	if (angle <= 0 || angle >= 180)
		parse_error("Radius must be positive", line_num);
	if (!str_to_rgb(&material.color, split[4]))
		parse_error("Invalid param: color value of the cone", line_num);
	if (!is_valid_float(split[5]))
		parse_error("Invalid param: specular value of the cone", line_num);
	material.specular = str_to_float(split[4]);
	if (material.specular < 0 || material.specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	cone = cone_new(&transform, &material, angle);
	rt->shapes = add_new_shape(rt->shapes, cone, CONE, &rt->cnt.cone);
}

void		parse_shape(t_rt *rt, char **split, int line_num)
{
	if (!split[1] || !split[2] || !split[3] || !split[4])
		parse_error("Incorrect count of the params for shape", line_num);
	if (ft_strequ(split[0], "plane") && split[5])
		parse_error("Incorrect count of the params for plane", line_num);
	if (ft_strequ(split[0], "cylinder") || ft_strequ(split[0], "cone") ||
		ft_strequ(split[0], "sphere"))
		if (!split[5] || split[6])
			parse_error("Incorrect count of the params for shape", line_num);
	if (ft_strequ(split[0], "plane"))
		parse_plane(rt, split, line_num);
	else if (ft_strequ(split[0], "sphere"))
		parse_sphere(rt, split, line_num);
	else if (ft_strequ(split[0], "cylinder"))
		parse_cylinder(rt, split, line_num);
	else if (ft_strequ(split[0], "cone"))
		parse_cone(rt, split, line_num);
}
