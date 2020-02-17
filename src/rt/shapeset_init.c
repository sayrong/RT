/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapeset_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 23:48:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 06:48:05 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_ray_direction(t_ray *r, t_vec2 *point, t_cam *cam)
{
	t_vec2	ratio;
	t_vec2	pos;
	t_vec3	point_on_plane;
	t_vec2	tmp;

	ratio = (t_vec2){(float)WIDTH / (float)HEIGHT / 2.0, 0.5};
	pos = (t_vec2){point->u / WIDTH, point->v / HEIGHT};
	tmp = (t_vec2){pos.u * ratio.u, pos.v * ratio.v};
	tmp = (t_vec2){tmp.u - ratio.u, tmp.v - ratio.v};
	point_on_plane = (t_vec3){tmp.u, tmp.v, 1.0};
	r->direction = v3_rot_y(v3_rot_x(point_on_plane,
		-cam->transform.rotation.y), -cam->transform.rotation.x);
}

void	init_ray(t_inter *inter, t_vec2 *mouse_pos, t_cam *cam)
{
	t_vec2	screen_coord;

	inter->ray.origin = cam->transform.position;
	inter->ray.t_max = RAY_T_MAX;
	inter->t = RAY_T_MAX;
	inter->shape = NULL;
	screen_coord = v2_set(mouse_pos->u / WIDTH - 1.0,
		(-2.0 * (HEIGHT - mouse_pos->v / 2)) / HEIGHT + 1.0);
	ft_printf("%f %f\n", screen_coord.u, screen_coord.v);
	set_ray_direction(&inter->ray, &screen_coord, cam);
}

_Bool	shape_intersect(t_inter *inter, t_list_shape *shape)
{
	t_cone	*cone;

	cone = NULL;
	if (shape->type == PLANE)
		return (plane_intersect(inter, shape));
	if (shape->type == SPHERE)
		return (sphere_intersect(inter, shape));
	if (shape->type == CONE)
		return (cone_intersect(inter, shape, cone));
	if (shape->type == CYLINDER)
		return (cylinder_intersect(inter, shape));
	return (FALSE);
}

_Bool	shapeset_intersect(t_inter *inter, t_list_shape *shape_list)
{
	_Bool			does_intersect;
	int				i;
	t_list_shape	*shape;

	i = 0;
	shape = shape_list;
	if (!inter)
		error("NULL in shapeset_intersect");
	does_intersect = FALSE;
	while (shape)
	{
		i += shape_intersect(inter, shape);
		shape = shape->next;
	}
	if (i > 0)
		does_intersect = TRUE;
	return (does_intersect);
}
