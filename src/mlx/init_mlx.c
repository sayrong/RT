/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:55:18 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 14:03:40 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_mlx(t_rt *rt)
{
	if (!(rt->mlx.mlx_ptr = mlx_init()))
		p_error("Failed to set up the connection to the X server");
	rt->mlx.win_ptr = mlx_new_window(rt->mlx.mlx_ptr, WIDTH, HEIGHT, "RT");
	!rt->mlx.win_ptr ? p_error("Failed to create a new window") : 0;
	rt->mlx.img = img_new(WIDTH, HEIGHT, rt);
	rt->mlx.rgb_spectrum = img_new(100, 100, rt);
	make_rgb_spectrum(rt->mlx.rgb_spectrum->data);
}
