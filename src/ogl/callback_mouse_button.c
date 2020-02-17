/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_mouse_button.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:44:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 06:47:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	middle_button(t_rt *rt, t_list_shape *shape)
{
	t_list_shape	*tmp;

	if (shape->marker == TRUE)
		rt->marker = NULL;
	if (rt->shapes == shape)
		rt->shapes = rt->shapes->next;
	else
	{
		tmp = rt->shapes;
		while (tmp->next != shape)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	del_shape(&shape, &rt->cnt);
}

static void	left_middle_press(t_rt *rt, int key)
{
	t_inter	inter;
	t_vec2	tmp;

	tmp = (t_vec2){(float)rt->mouse_x, (float)rt->mouse_y};
	init_ray(&inter, &tmp, &rt->cam);
	if (shapeset_intersect(&inter, rt->shapes))
	{
		if (key == GLFW_MOUSE_BUTTON_MIDDLE)
			return (middle_button(rt, inter.shape));
		inter.shape->marker ^= 1;
		if (!rt->marker)
			rt->marker = inter.shape;
		else if (rt->marker->marker == FALSE)
			rt->marker = NULL;
		else
		{
			rt->marker->marker = FALSE;
			rt->marker = inter.shape;
		}
		return ;
	}
	(rt->marker) ? rt->marker->marker = FALSE : 0;
	rt->marker = NULL;
}

void	callback_mouse_button(GLFWwindow *window, int key, int action, int mode)
{
	t_rt	*rt;

	++mode;
	rt = (t_rt*)glfwGetWindowUserPointer(window);
	if (key == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
			rt->flg.hold_rmb_ogl = TRUE;
		else if (action == GLFW_RELEASE)
			rt->flg.hold_rmb_ogl = FALSE;
	}
	else if ((key == GLFW_MOUSE_BUTTON_LEFT ||
			key == GLFW_MOUSE_BUTTON_MIDDLE) && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &rt->mouse_x, &rt->mouse_y);
		left_middle_press(rt, key);
	}
	else
		return ;
	rt->flg.run = TRUE;
}
