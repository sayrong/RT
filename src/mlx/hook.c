/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:52:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 02:54:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	red_x_button(void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	rt->flg.open_ui = FALSE;
	rt->flg.put_ui = FALSE;
	mlx_destroy_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr);
	rt->mlx.win_ptr = NULL;
	return (0);
}

void		input_hook(t_rt *rt)
{
	mlx_hook(rt->mlx.win_ptr, 2, 3, deal_key, (void *)rt);
//	mlx_hook(rt->mlx.win_ptr, 4, (1L << 2), mouse_press, (void *)rt);
//	mlx_hook(rt->mlx.win_ptr, 5, (1L << 3), mouse_release, (void *)rt);
//	mlx_hook(rt->mlx.win_ptr, 6, (1L << 6), mouse_move, (void*)rt);
	mlx_hook(rt->mlx.win_ptr, 17, 1, red_x_button, (void *)rt);
}
