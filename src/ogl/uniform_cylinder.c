/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:56:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 21:11:14 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_uniform_cylinder2(t_cylinder *shape, int index,
								GLuint shader_program, _Bool marker)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("cylinders[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	if (marker)
		glUniform3f(i, shape->material.color.r / 255.0,
			shape->material.color.g / 255.0, shape->material.color.b / 255.0);
	else
		glUniform3f(i, 1.0, 1.0, 1.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("cylinders[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(shape->material.specular, 0.0, 1000));
	ft_strdel(&combine);
	combine = combine_str_int_str("cylinders[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	ft_strdel(&combine);
}

void		set_uniform_cylinder(t_cylinder *shape, int index,
								GLuint shader_program, _Bool marker)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("cylinders[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, shape->transform.position.x, shape->transform.position.y,
		shape->transform.position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("cylinders[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, shape->transform.rotation.x, shape->transform.rotation.y,
		shape->transform.rotation.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("cylinders[", index, "].axis");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, 0.0, 0.0, 1.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("cylinders[", index, "].radius");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(shape->radius, 0.1, RAY_T_MAX / 10.0));
	ft_strdel(&combine);
	set_uniform_cylinder2(shape, index, shader_program, marker);
}
