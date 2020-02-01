/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:56:31 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 18:41:15 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_plane(t_rt *rt, char **split, int line_num)
{
	t_vec3	position;
	t_vec3	normal;
	int		specular;
	t_plane	*plane;

	if (!str_to_v3(&position, split[1]))
		parse_error("Invalid param: position point of the plane", line_num);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		parse_error("Normal vector must not be zero vector", line_num);
	if (!str_to_v3(&normal, split[2]))
		parse_error("Invalid param: normal vector of the plane", line_num);
	if (!str_to_integer(&specular, split[3]))
		parse_error("Invalid param: specular value of the plane", line_num);
	if (specular < 0 || specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	plane = plane_new(position, normal, specular);
	if (!str_to_rgb(&plane->color, split[4]))
		parse_error("Invalid param: color value of the plane", line_num);
	rt->shapes = add_new_shape(rt->shapes, plane, PLANE);
}

static void	parse_sphere(t_rt *rt, char **split, int line_num)
{
	t_vec3		center;
	double		radius;
	int			specular;
	t_sphere	*sphere;

	if (!str_to_v3(&center, split[1]))
		parse_error("Invalid param: center point of the sphere", line_num);
	if (!is_valid_double(split[2]))
		parse_error("Invalid param: radius value of the sphere", line_num);
	if ((radius = str_to_double(split[2])) <= 0)
		parse_error("Radius of the sphere must be positive", line_num);
	if (!str_to_integer(&specular, split[3]))
		parse_error("Invalid param: specular value of the sphere", line_num);
	if (specular < 0 || specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	sphere = sphere_new(center, radius, specular);
	if (!str_to_rgb(&sphere->color, split[4]))
		parse_error("Invalid param: color value of the sphere", line_num);
	rt->shapes = add_new_shape(rt->shapes, sphere, SPHERE);
}

static void	parse_cylinder(t_rt *rt, char **split, int line_num)
{
	t_vec3		pos_dir[2];
	double		radius;
	int			specular;
	t_cylinder	*cylinder;

	if (!str_to_v3(&pos_dir[0], split[1]))
		parse_error("Invalid param: position point of the cylinder", line_num);
	if (!str_to_v3(&pos_dir[1], split[2]))
		parse_error("Invalid param: direction vector of the cylinder",
					line_num);
	if (pos_dir[1].x == 0 && pos_dir[1].y == 0 && pos_dir[1].z == 0)
		parse_error("Direction vector must not be zero vector", line_num);
	if (!is_valid_double(split[3]))
		parse_error("Invalid param: radius value of the cylinder", line_num);
	if ((radius = str_to_double(split[3])) <= 0)
		parse_error("Radius of the cylinder must be positive", line_num);
	if (!str_to_integer(&specular, split[4]))
		parse_error("Invalid param: specular value of the cylinder", line_num);
	if (specular < 0 || specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	cylinder = cylinder_new(pos_dir[0], pos_dir[1], radius, specular);
	if (!str_to_rgb(&cylinder->color, split[5]))
		parse_error("Invalid param: color value of the cylinder", line_num);
	rt->shapes = add_new_shape(rt->shapes, cylinder, CYLINDER);
}

static void	parse_cone(t_rt *rt, char **split, int line_num)
{
	t_vec3	pos_dir[2];
	double	angle;
	int		specular;
	t_cone	*cone;

	if (!str_to_v3(&pos_dir[0], split[1]))
		parse_error("Invalid param: position point of the cone", line_num);
	if (!str_to_v3(&pos_dir[1], split[2]))
		parse_error("Invalid param: direction vector of the cone", line_num);
	if (pos_dir[1].x == 0 && pos_dir[1].y == 0 && pos_dir[1].z == 0)
		parse_error("Direction vector must not be zero vector", line_num);
	if (!is_valid_double(split[3]))
		parse_error("Invalid param: angle value of the cone", line_num);
	if ((angle = str_to_double(split[3])) <= 0 || angle >= 180)
		parse_error("Range for angle of the cone: (0...180)", line_num);
	if (!str_to_integer(&specular, split[4]))
		parse_error("Invalid param: specular value of the cone", line_num);
	if (specular < 0 || specular > 1000)
		parse_error("Range for specular of the shape: [0...1000]", line_num);
	cone = cone_new(pos_dir[0], pos_dir[1], angle, specular);
	if (!str_to_rgb(&cone->color, split[5]))
		parse_error("Invalid param: color value of the cone", line_num);
	rt->shapes = add_new_shape(rt->shapes, cone, CONE);
}

void		parse_shape(t_rt *rt, char **split, int line_num)
{
	if (!split[1] || !split[2] || !split[3] || !split[4])
		parse_error("Incorrect count of the params for shape", line_num);
	if (ft_strequ(split[0], "plane") || ft_strequ(split[0], "sphere"))
		if (split[5])
			parse_error("Incorrect count of the params for shape", line_num);
	if (ft_strequ(split[0], "cylinder") || ft_strequ(split[0], "cone"))
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
