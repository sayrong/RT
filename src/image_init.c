/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 02:46:12 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 15:42:04 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img	*img_new(int width, int height, t_rt *rt)
{
	t_img	*new_img;

	if (!(new_img = (t_img*)malloc(sizeof(t_img))))
		p_error("malloc t_img");
	if (!(new_img->img_ptr = mlx_new_image(rt->mlx_ptr, width, height)))
		p_error("Failed to create a new image");
	new_img->data = mlx_get_data_addr(new_img->img_ptr, &new_img->bpp,
									&new_img->size_line, &new_img->endian);
	if (!new_img->data)
		p_error("Failed to get data address");
	new_img->width = width;
	new_img->height = height;
	return (new_img);
}

int		*get_pixel(int x, int y, t_img *img)
{
	int	*data;

	data = (int*)img->data;
	return (data + (x + y * img->width));
}
