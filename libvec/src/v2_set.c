/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:27:07 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 14:34:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec2	v2_set(double u, double v)
{
	t_vec2	new_v2;

	new_v2.u = u;
	new_v2.v = v;
	return (new_v2);
}
