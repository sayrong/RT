/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_rot_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 21:17:48 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 20:49:15 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3	v3_rot_x(t_vec3 v, float angle)
{
	t_vec3	new_v;

	angle *= RAD;
	new_v.x = v.x;
	new_v.y = v.y * cos(angle) - v.z * sin(angle);
	new_v.z = v.y * sin(angle) + v.z * cos(angle);
	return (new_v);
}
