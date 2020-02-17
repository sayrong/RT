/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:44:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 06:47:44 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	middle_button(t_rt *rt, t_list_shape *shape)
{
	t_list_shape	*tmp;

	if (shape->marker == TRUE)
		rt->marker = NULL;
	if (rt->shapes == shape)
		rt->shapes = rt->shapes->next;
	else
	{
		tmp = rt->shapes;
		while (tmp->next != shape)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	del_shape(&shape, &rt->cnt);
}

static void	left_middle_button(t_rt *rt, int button, int x, int y)
{
	t_ray			r;
	t_inter			inter;
	t_vec2			screen_coord;

	screen_coord = v2_set((2.0 * x) / WIDTH - 1.0, (-2.0 * y) / HEIGHT + 1.0);
//	r.origin = rt->cam.origin;
	r.t_max = RAY_T_MAX;
	inter_new_ray(&inter, &r);
//	set_ray_direction(inter.ray, &screen_coord, &rt->cam);
	if (shapeset_intersect(&inter, rt->shapes))
	{
		if (button == SCROLL_CLICK)
			return (middle_button(rt, inter.shape));
		inter.shape->marker ^= 1;
		if (!rt->marker)
			rt->marker = inter.shape;
		else if (rt->marker->marker == FALSE)
			rt->marker = NULL;
		else
		{
			rt->marker->marker = FALSE;
			rt->marker = inter.shape;
		}
//		draw(rt);
	}
}

static void	scrolling(t_rt *rt, int button)
{
	t_shape_type	type;
	void			*shape;

	type = rt->marker->type;
	shape = rt->marker->shape;
	if (button == 4)
	{
		if (type == SPHERE)
			((t_sphere*)shape)->radius += 1;
		else if (type == CYLINDER)
			((t_cylinder*)shape)->radius += 1;
		else if (type == CONE && ((t_cone*)shape)->angle + 10 < 180)
			((t_cone*)shape)->angle += 10;
		else
			return ;
	}
	else if (type == SPHERE && ((t_sphere*)shape)->radius - 1 > 0)
		((t_sphere*)shape)->radius -= 1;
	else if (type == CYLINDER && ((t_cylinder*)shape)->radius - 1 > 0)
		((t_cylinder*)shape)->radius -= 1;
	else if (type == CONE && ((t_cone*)shape)->angle - 10 > 0)
		((t_cone*)shape)->angle -= 10;
	else
		return ;
//	draw(rt);
}

//static void	set_shape_color(t_rt *rt, t_color *shape_color, int *pixel)
//{
//	*shape_color = (t_color){(*pixel & 0xFF0000) >> 16,
//							(*pixel & 0xFF00) >> 8,
//							*pixel & 0xFF};
//	rt->flg.open_spectrum = FALSE;
//	draw(rt);
//}

int			mouse_move(int x, int y, void *param)
{
	t_rt	*rt;
	int		pixel;

	rt = (t_rt*)param;
	if (!rt->flg.hold_lmb_mlx || !rt->marker ||
	//!rt->flg.open_spectrum ||
			x < 0 || x >= 100 || y < 0 || y >= 100)
		return (0);
//	pixel = *get_pixel(x, y, rt->rgb_spectrum);
	pixel = 0;
	*get_color_from_list(rt->marker) = (t_color){(pixel & 0xFF0000) >> 16,
												(pixel & 0xFF00) >> 8,
												pixel & 0xFF};
//	draw(rt);
	return (0);
}

int			mouse_release(int button, int x, int y, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if (!rt->flg.hold_lmb_mlx || button != 1)
		return (0);
	++x;
	++y;
	rt->flg.hold_lmb_mlx = FALSE;
//	rt->flg.open_spectrum = FALSE;
//	draw(rt);
	return (0);
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if ((button != 1 && !rt->marker) && button != SCROLL_CLICK)
		return (0);
	if (button == 1 && rt->marker &&
	//rt->flg.open_spectrum &&
			x >= 0 && x < 100 && y >= 0 && y < 100)
	{
		rt->flg.hold_lmb_mlx = TRUE;
		mouse_move(x, y, param);
	}
//	else if (button == 1 && rt->marker &&
	//rt->flg.open_spectrum &&
//			x >= 0 && x < 100 && y >= 0 && y < 100)
//		set_shape_color(rt, get_color_from_list(rt->marker), 0);
//						get_pixel(x, y, rt->mlx.rgb_spectrum));
	else if (button == 1 || button == SCROLL_CLICK)
		left_middle_button(rt, button, x, y);
	else if (button == 4 || button == 5)
		scrolling(rt, button);
	return (0);
}
