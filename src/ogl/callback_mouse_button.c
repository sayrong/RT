/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_mouse_button.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:44:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 13:10:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	callback_mouse_button(GLFWwindow *window, int key, int action, int mode)
{
	t_rt	*rt;

	rt = (t_rt*)glfwGetWindowUserPointer(window);
	++mode;
	if (key == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
		}
		else if (action == GLFW_RELEASE)
		{
		}
	}
	else if (key == GLFW_MOUSE_BUTTON_LEFT)
	{
	}
}
