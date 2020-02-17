/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:03:54 by balvyn-s          #+#    #+#             */
/*   Updated: 2020/02/17 02:32:59 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	callback_key(GLFWwindow *window, int key, int scancode, int action)
{
	t_rt	*rt;

	rt = (t_rt*)glfwGetWindowUserPointer(window);
	++scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_U && action == GLFW_PRESS)
		!rt->flg.open_ui ? (rt->flg.put_ui = TRUE) : red_x_button((void*)rt);
}
