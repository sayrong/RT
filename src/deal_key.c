/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:03:54 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/10/14 22:44:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static _Bool	is_move(int key)
{
	return (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY ||
			key == Q_KEY || key == E_KEY);
}

static _Bool	is_rotate(int key)
{
	return (key == TWO_NUM || key == FOUR_NUM || key == SIX_NUM ||
			key == EIGHT_NUM);
}

static void		move_cam(t_cam *cam, int key)
{
	t_vec3	step;
	double	move;

	move = (key == W_KEY || key == D_KEY || key == E_KEY) ? MOVE : -MOVE;
	step = v3_sub(cam->target, cam->origin);
	if (key == A_KEY || key == D_KEY)
		step = v3_cross(step, cam->up);
	else if (key == Q_KEY || key == E_KEY)
		step = v3_cross(step, cam->right);
	step = v3_scale(step, move);
	cam->origin = v3_add(cam->origin, step);
	cam->target = v3_add(cam->target, step);
	*cam = camera_new(cam->origin, cam->target);
}

static void		rotate_cam(t_cam *cam, int key)
{
	t_vec3	step;
	double	angle;

	angle = (key == EIGHT_NUM || key == SIX_NUM) ? -ANGLE : ANGLE;
	step = v3_sub(cam->target, cam->origin);
	if (key == SIX_NUM || key == FOUR_NUM)
		step = v3_rot_y(step, angle);
	else if (key == TWO_NUM || key == EIGHT_NUM)
		step = v3_rot_x(step, angle);
	cam->target = v3_add(cam->origin, step);
	*cam = camera_new(cam->origin, cam->target);
}

int				deal_key(int key, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if (key == ESC)
		red_x_button(param);
	if (is_move(key))
		move_cam(&rt->cam, key);
	else if (is_rotate(key))
		rotate_cam(&rt->cam, key);
	else if (key == P_KEY)
		rt->play ^= TRUE;
	draw(rt);
	return (0);
}
