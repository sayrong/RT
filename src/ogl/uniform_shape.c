/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:18:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 19:34:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_uniform_plane(t_plane *plane, int index, GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("shapes[", index, "].position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, plane->position.x, plane->position.y, plane->position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, plane->specular);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, plane->color.r / 255.0, plane->color.g / 255.0,
				plane->color.b / 255.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].plane.normal");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, plane->normal.x, plane->normal.y, plane->normal.z);
	ft_strdel(&combine);
}

static void	set_uniform_sphere(t_sphere *sphere, int index,
							GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	combine = combine_str_int_str("shapes[", index, "].position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, sphere->center.x, sphere->center.y, sphere->center.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, sphere->specular);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, sphere->color.r / 255.0, sphere->color.g / 255.0,
				sphere->color.b / 255.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].sphere.radius");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, sphere->radius);
	ft_strdel(&combine);
}

static void	set_uniform_cylinder(t_cylinder *cylinder, int index,
							GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("shapes[", index, "].position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, cylinder->position.x, cylinder->position.y,
				cylinder->position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, cylinder->specular);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cylinder->color.r / 255.0, cylinder->color.g / 255.0,
				cylinder->color.b / 255.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].cylinder.dir");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, cylinder->dir.x, cylinder->dir.y, cylinder->dir.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].cylinder.radius");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1d(i, cylinder->radius);
	ft_strdel(&combine);
}

static void	set_uniform_cone(t_cone *cone, int index, GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("shapes[", index, "].position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, cone->position.x, cone->position.y, cone->position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, cone->specular);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cone->color.r / 255.0, cone->color.g / 255.0,
				cone->color.b / 255.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].cylinder.dir");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3d(i, cone->dir.x, cone->dir.y, cone->dir.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].cylinder.angle");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1d(i, cone->angle);
	ft_strdel(&combine);
}

void		set_uniform_shape(t_list_shape *shape, int index,
							GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("shapes[", index, "].type");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, shape->shape);
	ft_strdel(&combine);
	combine = combine_str_int_str("shapes[", index, "].marker");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, shape->marker);
	ft_strdel(&combine);
	if (shape->shape == PLANE)
		set_uniform_plane((t_plane*)shape->content, index, shader_program);
	else if (shape->shape == SPHERE)
		set_uniform_sphere((t_sphere*)shape->content, index, shader_program);
	else if (shape->shape == CYLINDER)
		set_uniform_cylinder((t_cylinder*)shape->content, index,
							shader_program);
	else if (shape->shape == CONE)
		set_uniform_cone((t_cone*)shape->content, index, shader_program);
}
