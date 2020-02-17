/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:26:41 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 19:35:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_uniform_sphere2(t_sphere *shape, int index,
								GLuint shader_program, _Bool marker)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("spheres[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	if (marker)
		glUniform3f(i, shape->material.color.r / 255.0,
			shape->material.color.g / 255.0, shape->material.color.b / 255.0);
	else
		glUniform3f(i, 1.0, 1.0, 1.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("spheres[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(shape->material.specular, 0.0, 1000.0));
	ft_strdel(&combine);
	combine = combine_str_int_str("spheres[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	ft_strdel(&combine);
	combine = combine_str_int_str("spheres[", index, "].isOutline");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, 0);
	ft_strdel(&combine);
}

void		set_uniform_sphere(t_sphere *shape, int index,
								GLuint shader_program, _Bool marker)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("spheres[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, shape->transform.position.x, shape->transform.position.y,
		shape->transform.position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("spheres[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, shape->transform.rotation.x, shape->transform.rotation.y,
	shape->transform.rotation.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("spheres[", index, "].radius");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(shape->radius, 0.1, RAY_T_MAX / 10.0));
	ft_strdel(&combine);
	set_uniform_sphere2(shape, index, shader_program, marker);
	combine = combine_str_int_str("spheres[", index, "].isToon");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, 0);
	ft_strdel(&combine);
}
