/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:26:38 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 18:41:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_uniform_light2(t_light *light, int index, GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("lights[", index, "].intensity");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(light->intensity, 0.0, 100.0));
	ft_strdel(&combine);
	if (light->type == POINT)
	{
		combine = combine_str_int_str("lights[", index, "].direction");
		i = glGetUniformLocation(shader_program, combine);
		glUniform3f(i, clamp(light->radius, 0.1, RAY_T_MAX / 10.0), 0.0, 0.0);
		ft_strdel(&combine);
	}
}

void		set_uniform_light(t_light *light, int index, GLuint shader_program)
{
	GLuint	i;
	char	*combine;
	t_vec3	tmp;

	combine = combine_str_int_str("lights[", index, "].type");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, light->type);
	ft_strdel(&combine);
	combine = combine_str_int_str("lights[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, light->transform.position.x, light->transform.position.y,
		light->transform.position.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("lights[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, light->transform.rotation.x, light->transform.rotation.y,
		light->transform.rotation.z);
	ft_strdel(&combine);
	combine = combine_str_int_str("lights[", index, "].direction");
	i = glGetUniformLocation(shader_program, combine);
	tmp = v3_norm(light->direction);
	glUniform3f(i, tmp.x, tmp.y, tmp.z);
	ft_strdel(&combine);
	set_uniform_light2(light, index, shader_program);
}
