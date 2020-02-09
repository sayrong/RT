/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:45:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 20:32:45 by cschoen          ###   ########.fr       */
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

static void	set_main_settings(GLuint shader_program, t_rt *rt)
{
	GLint	i;

	i = glGetUniformLocation(shader_program, "resolution");
	glUniform2f(i, (GLfloat)WIDTH, (GLfloat)HEIGHT);
	i = glGetUniformLocation(shader_program, "flag.is_anti_alias");
	glUniform1i(i, rt->flg.is_anti_alias);
	i = glGetUniformLocation(shader_program, "LIGHT_CNT");
	glUniform1i(i, rt->lights_cnt);
	i = glGetUniformLocation(shader_program, "SHAPE_CNT");
	glUniform1i(i, rt->shapes_cnt);
	i = glGetUniformLocation(shader_program, "inter.ray.origin");
	glUniform3f(i, rt->cam.origin.x, rt->cam.origin.y, rt->cam.origin.z);
	i = glGetUniformLocation(shader_program, "inter.ray.t_max");
	glUniform1f(i, RAY_T_MAX);
	i = glGetUniformLocation(shader_program, "inter.t");
	glUniform1f(i, RAY_T_MAX);
}

static void	set_uniform_cam(t_cam *camera, GLuint shader_program)
{
	GLuint	i;

	i = glGetUniformLocation(shader_program, "cam.h");
	glUniform1d(i, camera->h);
	i = glGetUniformLocation(shader_program, "cam.w");
	glUniform1d(i, camera->w);
	i = glGetUniformLocation(shader_program, "cam.origin");
	glUniform3d(i, camera->origin.x, camera->origin.y, camera->origin.z);
	i = glGetUniformLocation(shader_program, "cam.forward");
	glUniform3d(i, camera->forward.x, camera->forward.y, camera->forward.z);
	i = glGetUniformLocation(shader_program, "cam.up");
	glUniform3d(i, camera->up.x, camera->up.y, camera->up.z);
	i = glGetUniformLocation(shader_program, "cam.right");
	glUniform3d(i, camera->right.x, camera->right.y, camera->right.z);
}

static void	set_uniform_light(t_light *light, int index, GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("lights[", index, "].type");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, light->type);
	ft_strdel(&combine);
	combine = combine_str_int_str("lights[", index, "].intensity");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1d(i, light->intensity);
	ft_strdel(&combine);
	if (light->type == POINT)
	{
		combine = combine_str_int_str("lights[", index, "].position");
		i = glGetUniformLocation(shader_program, combine);
		glUniform3d(i, light->position.x, light->position.y, light->position.z);
		ft_strdel(&combine);
	}
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
	while (!light && ++i < MAX_CNT_LIGHTS)
	{
		set_uniform_light(light->light, i, shader_program);
		light = light->next;
	}
	shape = rt->shapes;
	i = -1;
	while (!shape && ++i < MAX_CNT_SHAPES)
	{
		set_uniform_shape(shape, i, shader_program);
		shape = shape->next;
	}
}
