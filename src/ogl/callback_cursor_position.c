/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_cursor_position.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 12:03:53 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 21:03:07 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	callback_cursor_position(GLFWwindow *window, float xpos, float ypos)
{
	if (window)
	{
		xpos += 1;
		ypos += 1;
	}
}
