/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:21:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 03:12:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	run(t_rt *rt)
{
	glfwPollEvents();
	if (!rt->flg.run && !rt->flg.hold_rmb_ogl)
		return ;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(rt->gl.shader_program);
	set_settings(rt, rt->gl.shader_program);
	glBindVertexArray(rt->gl.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glfwSwapBuffers(rt->gl.window);
	ft_putendl("ad");
	rt->flg.run = FALSE;
}
