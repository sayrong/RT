/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:58:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 20:37:05 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	get_normal(t_inter *inter)
{
	t_vec3	hit_point;
	t_vec3	tmp;

	tmp = v3_scale(inter->ray->direction, inter->t);
	hit_point = v3_add(inter->ray->origin, tmp);
	if (inter->shape->shape == SPHERE)
		return (get_sphere_normal((t_sphere*)inter->shape->content, hit_point));
	else if (inter->shape->shape == PLANE)
		return (get_plane_normal((t_plane*)inter->shape->content, inter->ray));
	else if (inter->shape->shape == CONE)
		return (get_cone_normal((t_cone*)inter->shape->content, inter->ray,
							hit_point, inter->t));
	else
		return (get_cyl_normal((t_cylinder*)inter->shape->content, inter->ray,
							hit_point, inter->t));
}

int		get_specular(t_inter *inter)
{
	if (inter->shape->shape == SPHERE)
		return ((t_sphere*)inter->shape->content)->specular;
	else if (inter->shape->shape == PLANE)
		return ((t_plane*)inter->shape->content)->specular;
	else if (inter->shape->shape == CONE)
		return ((t_cone*)inter->shape->content)->specular;
	else
		return ((t_cylinder*)inter->shape->content)->specular;
}

void	send_ray(t_inter *inter, int position, t_thread *src)
{
	int		x_y[2];
	int		*cur_pixel;
	double	aliasing_incrementer;

	x_y[0] = position % WIDTH;
	x_y[1] = position / HEIGHT;
	aliasing_incrementer = src->rt->is_anti_alias ? 0.25 : 1;
	cur_pixel = get_pixel(x_y[0], x_y[1], src->rt->img);
	*cur_pixel = anti_aliasing(inter, x_y, src, aliasing_incrementer);
}

void	*calculate(void *data)
{
	inter_new_ray(&inter, &r);
	while (start_end[0] < start_end[1])
	{
		send_ray(&inter, start_end[0], src);
		start_end[0]++;
	}
}
