/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:03:54 by balvyn-s          #+#    #+#             */
/*   Updated: 2020/02/17 03:00:28 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

_Bool	is_move(int key)
{
	return (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY ||
			key == Q_KEY || key == E_KEY);
}

_Bool	is_shape_move(int key)
{
	return (key == UP || key == DOWN || key == LEFT || key == RIGHT ||
			key == R_SHIFT || key == R_CTRL);
}

_Bool	is_rotate(int key)
{
	return (key == TWO_NUM || key == FOUR_NUM || key == SIX_NUM ||
			key == EIGHT_NUM);
}

// void		move_cam(t_cam *cam, int key)
// {
// 	t_vec3	step;
// 	double	move;

// 	move = (key == W_KEY || key == D_KEY || key == E_KEY) ? MOVE : -MOVE;
// 	step = v3_sub(cam->target, cam->origin);
// 	if (key == A_KEY || key == D_KEY)
// 		step = v3_cross(step, cam->up);
// 	else if (key == Q_KEY || key == E_KEY)
// 		step = v3_cross(step, cam->right);
// 	step = v3_scale(step, move);
// 	cam->origin = v3_add(cam->origin, step);
// 	cam->target = v3_add(cam->target, step);
// 	*cam = camera_new(cam->origin, cam->target);
// }

// void		move_shape(t_list_shape *shape, int key, t_cam *cam)
// {
// 	t_vec3	step;
// 	double	move;

// 	move = (key == UP || key == RIGHT || key == R_CTRL) ? MOVE : -MOVE;
// 	step = v3_sub(cam->target, cam->origin);
// 	if (key == LEFT || key == RIGHT)
// 		step = v3_cross(step, cam->up);
// 	else if (key == R_SHIFT || key == R_CTRL)
// 		step = v3_cross(step, cam->right);
// 	step = v3_scale(step, move);
// 	if (shape->shape == SPHERE)
// 		((t_sphere*)shape->content)->center =
// 			v3_add(((t_sphere*)shape->content)->center, step);
// 	else if (shape->shape == CYLINDER)
// 		((t_cylinder*)shape->content)->position =
// 			v3_add(((t_cylinder*)shape->content)->position, step);
// 	else if (shape->shape == CONE)
// 		((t_cone*)shape->content)->position =
// 			v3_add(((t_cone*)shape->content)->position, step);
// 	else if (shape->shape == PLANE)
// 		((t_plane*)shape->content)->position =
// 			v3_add(((t_plane*)shape->content)->position, step);
// }

// void		rotate_cam(t_cam *cam, int key)
// {
// 	t_vec3	step;
// 	double	angle;

// 	angle = (key == EIGHT_NUM || key == SIX_NUM) ? -ANGLE : ANGLE;
// 	step = v3_sub(cam->target, cam->origin);
// 	if (key == SIX_NUM || key == FOUR_NUM)
// 		step = v3_rot_y(step, angle);
// 	else if (key == TWO_NUM || key == EIGHT_NUM)
// 		step = v3_rot_x(step, angle);
// 	cam->target = v3_add(cam->origin, step);
// 	*cam = camera_new(cam->origin, cam->target);
// }

int				deal_key(int key, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if (key == ESC || key == U_KEY)
		red_x_button(param);
//	if (key == P_KEY)
//		rt->play ^= TRUE;
//	else if (key == M_KEY)
//		rt->is_anti_alias = !rt->is_anti_alias;
//	else if (key == C_KEY && rt->marker)
//		rt->flg.open_spectrum ^= TRUE;
//	else if (is_move(key))
//		move_cam(&rt->cam, key);
//	else if (is_rotate(key))
//		rotate_cam(&rt->cam, key);
//	else if (rt->marker && is_shape_move(key))
//		move_shape(rt->marker, key, &rt->cam);
	else
		return (0);
//	draw(rt);
	return (0);
}
