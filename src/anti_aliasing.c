/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:58:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 21:18:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//https://ru.wikipedia.org/wiki/Избыточная_выборка_сглаживания
//М - чтобы выключить/включить

t_color	color_mid(t_color c1, int hit)
{
	t_color	color;

	color.r = c1.r / hit;
	color.g = c1.g / hit;
	color.b = c1.b / hit;
	return (color);
}

void	make_average(t_color *color, double *light, int hit)
{
	if (hit != 0)
	{
		*light = *light / hit;
		*color = color_mid(*color, hit);
	}
}

void	init_ray(t_inter *inter, double *tmp_xy, t_thread *src)
{
	t_vec2	screen_coord;

	inter->t = RAY_T_MAX;
	screen_coord = v2_set((2.0 * tmp_xy[0]) / WIDTH - 1.0,
						  (-2.0 * tmp_xy[1]) / HEIGHT + 1.0);
	set_ray_direction(inter->ray, &screen_coord, &src->rt->cam);
}

int		anti_aliasing(t_inter *inter, int *xy, t_thread *src, double incrementer)
{
	double		tmp_xy[2];
	t_color		total_color;
	double		total_light;
	int			hit;

	init_aliasing(tmp_xy, xy, &total_light, &hit);
	total_color = (t_color){0, 0, 0};
	while (tmp_xy[0] < xy[0] + 1)
	{
		tmp_xy[1] = xy[1];
		while (tmp_xy[1] < xy[1] + 1)
		{
			init_ray(inter, tmp_xy, src);
			if (shapeset_intersect(inter, src->rt->shapes) && ++hit)
			{
				total_light += compute_light(inter, src->rt->shapes, src->rt->lights);
				if (!src->rt->marker || inter->shape->marker == TRUE)
					total_color = color_add(total_color, *(get_color_from_list(inter->shape)));
				else
					total_color = color_add(total_color, (t_color){255, 255, 255});
			}
			tmp_xy[1] += incrementer;
		}
		tmp_xy[0] += incrementer;
	}
	make_average(&total_color, &total_light, hit);
	return get_color(&(total_color), total_light);
}
