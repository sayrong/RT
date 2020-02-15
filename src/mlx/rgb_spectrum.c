/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 02:46:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 13:20:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_brightness(int spectrum, int bright)
{
	double	f;
	t_color	c;

	if (bright == 50)
		return (spectrum);
	f = (bright - 50) / 50.0;
	c = (t_color){(spectrum & 0xFF0000) >> 16, (spectrum & 0xFF00) >> 8,
					spectrum & 0xFF};
	c.r += ((bright > 50) ? (256 - c.r) : c.r) * f;
	c.g += ((bright > 50) ? (256 - c.g) : c.g) * f;
	c.b += ((bright > 50) ? (256 - c.b) : c.b) * f;
	if (c.r < 0 || c.r > 255)
		c.r = (c.r < 0) ? 0 : 255;
	if (c.g < 0 || c.g > 255)
		c.g = (c.g < 0) ? 0 : 255;
	if (c.b < 0 || c.b > 255)
		c.b = (c.b < 0) ? 0 : 255;
	return (c.r << 16 | c.g << 8 | c.b);
}

static int	get_spectrum(int index)
{
	double	f;

	if (index == 0 || index == 99)
		return (0xFF << 16 | 0x00 << 8 | 0x00);
	f = (index - (index / 25) * 25) / 25.0;
	if (index / 25 == 0)
		return (0xFF << 16 | (0x00 + (int)(f * (0xFF - 0x00))) << 8 | 0x00);
	if (index / 25 == 1)
		return ((0xFF + (int)(f * (0x00 - 0xFF))) << 16 | 0xFF << 8 |
					(0x00 + (int)(f * (0xFF - 0x00))));
	if (index / 25 == 2)
		return ((0x00 + (int)(f * (0xFF - 0x00))) << 16 |
					(0xFF + (int)(f * (0x00 - 0xFF))) << 8 | 0xFF);
	return (0xFF << 16 | 0x00 << 8 | (0xFF + (int)(f * (0x00 - 0xFF))));
}

/* спектр с другими диапазонами
static int	get_spectrum(int index)
{
	double	f;

	if (index == 0 || index == 99)
		return (0xFF << 16 | 0x00 << 8 | 0x00);
	if (index < 15)
	{
		f = index / 15.0;
		return (0xFF << 16 | (0x00 + (int)(f * (0xFF - 0x00))) << 8 | 0x00);
	}
	if (index >= 15 && index < 50)
	{
		f = (index - 15) / 35.0;
		return ((0xFF + (int)(f * (0x00 - 0xFF))) << 16 | 0xFF << 8 |
					(0x00 + (int)(f * (0xFF - 0x00))));
	}
	if (index >= 50 && index < 80)
	{
		f = (index - 50) / 30.0;
		return ((0x00 + (int)(f * (0xFF - 0x00))) << 16 |
					(0xFF + (int)(f * (0x00 - 0xFF))) << 8 | 0xFF);
	}
	f = (index - 80) / 20.0;
	return (0xFF << 16 | 0x00 << 8 | (0xFF + (int)(f * (0x00 - 0xFF))));
}
*/

void		make_rgb_spectrum(char *data)
{
	int	x;
	int	y;
	int	*i;

	i = (int*)data;
	y = -1;
	while (++y < 100)
	{
		x = -1;
		while (++x < 100)
			i[y * 100 + x] = get_brightness(get_spectrum(x), y);
	}
}
