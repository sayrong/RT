/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 01:04:34 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 03:03:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	put_ui(t_rt *rt)
{
	rt->flg.put_ui = FALSE;
	rt->flg.open_ui = TRUE;
	rt->mlx.win_ptr = mlx_new_window(rt->mlx.mlx_ptr, UI_W, UI_H, "INTERFACE");
	!rt->mlx.win_ptr ? p_error("Failed to create a new window") : 0;
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
							rt->mlx.rgb->img_ptr, 0,
							UI_H - SPECTRUM_W);
	mlx_do_sync(rt->mlx.mlx_ptr);
}

void		mlx_run(t_rt *rt)
{
	if (rt->flg.put_ui)
		put_ui(rt);
	if (rt->mlx.win_ptr)
		input_hook(rt);
}
