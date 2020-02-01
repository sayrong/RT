/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:59:26 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 16:55:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	inter_new_ray(t_inter *inter, t_ray *ray)
{
	inter->ray = ray;
	inter->t = RAY_T_MAX;
	inter->shape = NULL;
}

void	set_ray_direction(t_ray *r, t_vec2 *point, t_cam *cam)
{
	t_vec3	tmp;

	tmp = v3_scale(cam->right, point->u * cam->w);
	r->direction = v3_scale(cam->up, point->v * cam->h);
	r->direction = v3_add(r->direction, tmp);
	r->direction = v3_add(r->direction, cam->forward);
	r->direction = v3_norm(r->direction);
}
