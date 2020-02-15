/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:46 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 14:16:34 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_ui(t_rt *rt)
{
	pthread_t	thread;

	if (rt->marker == NULL)
		rt->flg.is_rgb = FALSE;
	if (pthread_create(thread, NULL, calculate, &rt))
		p_error("pthread_create");
	if (pthread_join(thread, NULL))
		p_error("pthread_join");
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
							rt->mlx.img->img_ptr, 0, 0);
	if (rt->flg.is_rgb)
		mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
								rt->mlx.rgb_spectrum->img_ptr, 0, 0);
	mlx_do_sync(rt->mlx.mlx_ptr);
}
