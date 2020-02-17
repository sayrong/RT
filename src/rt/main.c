/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:32:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 03:09:22 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_rt(t_rt *rt)
{
	rt->lights = NULL;
	rt->shapes = NULL;
	rt->marker = NULL;
	rt->cnt.light = 0;
	rt->cnt.plane = 0;
	rt->cnt.sphere = 0;
	rt->cnt.cone = 0;
	rt->cnt.cylinder = 0;
	rt->flg.cam_flg = FALSE;
	rt->flg.amb_flg = FALSE;
	rt->flg.run = TRUE;
	rt->flg.hold_rmb_ogl = FALSE;
	rt->flg.hold_lmb_mlx = FALSE;
	rt->flg.play = FALSE;
	rt->flg.put_ui = FALSE;
	rt->flg.open_ui = FALSE;
	rt->flg.is_anti_alias = FALSE;
}

int			main(int argc, char **argv)
{
	t_rt	rt;
	int		fd;

	if (argc != 2)
		usage(argv[0]);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		p_error("Can't open the scene file");
	init_rt(&rt);
	parser(&rt, fd);
	init_ogl(&rt);
	init_mlx(&rt);
	while (!glfwWindowShouldClose(rt.gl.window))
	{
		mlx_run(&rt);
		run(&rt);
	}
	glfwTerminate();
	return (0);
}
