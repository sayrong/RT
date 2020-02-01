/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 01:59:27 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 22:33:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam	camera_new(t_vec3 origin, t_vec3 target)
{
	t_cam	new_cam;
	t_vec2	fov_ratio;
	t_vec3	upguide;

	fov_ratio = v2_set(25.0 * PI / 180, (double)WIDTH / (double)HEIGHT);
	upguide = v3_new(0.0, 1.0, 0.0);
	new_cam.origin = origin;
	new_cam.target = target;
	new_cam.forward = v3_sub(target, origin);
	new_cam.forward = v3_norm(new_cam.forward);
	new_cam.right = v3_cross(new_cam.forward, upguide);
	if (v3_length(new_cam.right) < 0.0000001)
		new_cam.right = v3_cross(new_cam.forward, v3_new(1.0, 0.0, 0.0));
	new_cam.right = v3_norm(new_cam.right);
	new_cam.up = v3_cross(new_cam.right, new_cam.forward);
	new_cam.h = tan(fov_ratio.u);
	new_cam.w = new_cam.h * fov_ratio.v;
	return (new_cam);
}
