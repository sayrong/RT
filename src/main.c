/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:32:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 18:39:34 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_init(t_rt *rt)
{
	rt->lights = NULL;
	rt->shapes = NULL;
	rt->marker = NULL;
	rt->lights_cnt = 0;
	rt->shapes_cnt = 0;
	rt->flg.cam_flg = FALSE;
	rt->flg.amb_flg = FALSE;
	rt->flg.is_rgb = FALSE;
	rt->flg.is_move = TRUE;
	rt->flg.is_anti_alias = FALSE;
}

int			main(int argc, char **argv)
{
	t_rt	rt;
	int		fd;
	int		parse_line;

	fd = 0;
	parse_line = 0;
	if (argc != 2)
		usage(argv[0]);
	rt_init(&rt);
	parser(argv[1], &rt, fd, parse_line);
	gl_init(&rt);
	while (!glfwWindowShouldClose(rt.gl.window))
		draw(&rt);
	glfwTerminate();
	return (0);
}
