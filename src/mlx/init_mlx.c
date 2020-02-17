/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:55:18 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 02:38:02 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_mlx(t_rt* rt)
{
	if (!(rt->mlx.mlx_ptr = mlx_init()))
		p_error("Failed to set up the connection to the X server");
	rt->mlx.win_ptr = NULL;
//	rt->mlx.img = new_img(UI_W, UI_H, rt);
	rt->mlx.rgb = new_img(SPECTRUM_W, SPECTRUM_W, rt);
	make_rgb_spectrum(rt->mlx.rgb->data);
}
