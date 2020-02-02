/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 21:11:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/02 21:12:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	del_shape(t_list_shape **shape)
{
	if (shape && *shape)
	{
		ft_memdel(&(*shape)->content);
		ft_memdel((void**)shape);
	}
}
