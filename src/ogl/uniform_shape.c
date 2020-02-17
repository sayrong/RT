/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:18:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 21:07:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_uniform_shape(t_list_shape *shape, int index, GLuint shader_program,
						_Bool marker)
{
	if (shape->type == PLANE)
		set_uniform_plane((t_plane*)shape->shape, index, shader_program,
			marker);
	else if (shape->type == SPHERE)
		set_uniform_sphere((t_sphere*)shape->shape, index, shader_program,
			marker);
	else if (shape->type == CYLINDER)
		set_uniform_cylinder((t_cylinder*)shape->shape, index, shader_program,
			marker);
	else if (shape->type == CONE)
		set_uniform_cone((t_cone*)shape->shape, index, shader_program, marker);
}
