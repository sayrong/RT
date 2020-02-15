/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_rot_y.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 21:24:32 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 20:49:15 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3	v3_rot_y(t_vec3 v, float angle)
{
	t_vec3	new_v;

	angle *= RAD;
	new_v.x = v.x * cos(angle) + v.z * sin(angle);
	new_v.y = v.y;
	new_v.z = v.z * cos(angle) - v.x * sin(angle);
	return (new_v);
}
