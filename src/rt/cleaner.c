/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 21:11:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 03:59:16 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	del_shape(t_list_shape **shape, t_counter *cnt)
{
	if (shape && *shape)
	{
		if ((*shape)->type == PLANE)
			--cnt->plane;
		else if ((*shape)->type == SPHERE)
			--cnt->sphere;
		else if ((*shape)->type == CYLINDER)
			--cnt->cylinder;
		else if ((*shape)->type == CONE)
			--cnt->cone;
		ft_memdel(&(*shape)->shape);
		ft_memdel((void**)shape);
	}
}
