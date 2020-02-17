/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:56:15 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 21:08:06 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_uniform_cone2(t_cone *shape, int index, GLuint shader_program,
							_Bool marker)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("cones[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	if (marker)
		glUniform3f(i, shape->material.color.r / 255.0,
			shape->material.color.g / 255.0, shape->material.color.b / 255.0);
	else
		glUniform3f(i, 1.0, 1.0, 1.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("cones[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(shape->material.specular, 0.0, 1000.0));
	ft_strdel(&combine);
	combine = combine_str_int_str("cones[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	ft_strdel(&combine);
}

void		set_uniform_cone(t_cone *shape, int index, GLuint shader_program,
							_Bool marker)
{
	GLuint		i;
	char		*combine;

	combine = combine_str_int_str("cones[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, shape->transform.position.x, shape->transform.position.y,
	shape->transform.position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("cones[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, shape->transform.rotation.x, shape->transform.rotation.y,
	shape->transform.rotation.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("cones[", index, "].axis");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, 0.0, 1.0, 0.0);
	ft_strdel(&combine);
	combine = combine_str_int_str("cones[", index, "].angle");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(shape->angle / 180 * M_PI, 0.0001, M_PI_2 - 0.0001));
	ft_strdel(&combine);
	set_uniform_cone2(shape, index, shader_program, marker);
}
