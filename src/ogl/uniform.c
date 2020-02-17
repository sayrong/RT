/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:45:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 21:57:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*combine_str_int_str(char *str1, int number, char *str2)
{
	char	*ntos;
	char	*result;

	if (!(ntos = ft_itoa(number)))
		p_error("ft_itoa");
	result = ft_strnew(ft_strlen(str1) + ft_strlen(ntos) + ft_strlen(str2));
	if (!result)
		p_error("ft_strnew");
	ft_strcat(result, str1);
	ft_strcat(result, ntos);
	ft_strcat(result, str2);
	ft_strdel(&ntos);
	return (result);
}

float		clamp(float number, float min, float max)
{
	if (number > max)
		return (max);
	else if (number < min)
		return (min);
	else
		return (number);
}

static void	set_main_settings(GLuint shader_program, t_rt *rt)
{
	GLint	i;

	i = glGetUniformLocation(shader_program, "resolution");
	glUniform2f(i, (GLfloat)WIDTH, (GLfloat)HEIGHT);
	i = glGetUniformLocation(shader_program, "render_type");
	glUniform1i(i, 0);
	i = glGetUniformLocation(shader_program, "CONE_COUNT");
	glUniform1i(i, rt->cnt.cone);
	i = glGetUniformLocation(shader_program, "CYLINDER_COUNT");
	glUniform1i(i, rt->cnt.cylinder);
	i = glGetUniformLocation(shader_program, "PLANE_COUNT");
	glUniform1i(i, rt->cnt.plane);
	i = glGetUniformLocation(shader_program, "SPHERE_COUNT");
	glUniform1i(i, rt->cnt.sphere);
	i = glGetUniformLocation(shader_program, "LIGHT_COUNT");
	glUniform1i(i, rt->cnt.light);
}

static void	set_uniform_cam(t_cam *camera, GLuint shader_program)
{
	GLuint	i;

	i = glGetUniformLocation(shader_program, "camera.direction");
	glUniform3f(i, camera->direction.x, camera->direction.y,
		camera->direction.z);
	i = glGetUniformLocation(shader_program, "camera.transform.position");
	glUniform3f(i, camera->transform.position.x, camera->transform.position.y,
		camera->transform.position.z);
	i = glGetUniformLocation(shader_program, "camera.transform.rotation");
	glUniform3f(i, camera->transform.rotation.x, camera->transform.rotation.y,
		camera->transform.rotation.z);
}

void		set_settings(t_rt *rt, GLuint shader_program)
{
	int				i;
	t_list_light	*light;
	t_list_shape	*shape;

	set_main_settings(shader_program, rt);
	set_uniform_cam(&rt->cam, shader_program);
	light = rt->lights;
	i = -1;
	while (light && ++i < MAX_CNT_LIGHTS)
	{
		set_uniform_light(light->light, i, shader_program);
		light = light->next;
	}
	shape = rt->shapes;
	i = -1;
	while (shape && ++i < MAX_CNT_SHAPES)
	{
		set_uniform_shape(shape, i, shader_program,
			(!rt->marker || shape->marker));
		shape = shape->next;
	}
}
