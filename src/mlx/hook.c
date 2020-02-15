/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:52:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 13:54:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			red_x_button(void *param)
{
	(void)param;
	exit(0);
}

static int	no_hook(void *param)
{
	t_rt	*rt;
	t_vec3	step;

	rt = (t_rt*)param;
	if (rt->flg.play)
	{
		step = v3_sub(rt->cam.origin, rt->cam.target);
		step = v3_rot_y(step, ANGLE);
		rt->cam.origin = v3_add(rt->cam.target, step);
		rt->cam = camera_new(rt->cam.origin, rt->cam.target);
		draw(rt);
	}
	return (0);
}

static void	input_hook(t_rt *rt)
{
	mlx_hook(rt->mlx.win_ptr, 4, (1L << 2), mouse_press, (void *)rt);
	mlx_hook(rt->mlx.win_ptr, 5, (1L << 3), mouse_release, (void *)rt);
	mlx_hook(rt->mlx.win_ptr, 17, 1, red_x_button, (void *)0);
	mlx_hook(rt->mlx.win_ptr, 2, 3, deal_key, (void *)rt);
	mlx_hook(rt->mlx.win_ptr, 6, (1L << 6), mouse_move, (void*)rt);
	mlx_loop_hook(rt->mlx.mlx_ptr, no_hook, (void*)rt);
}
