/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:47:50 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 13:03:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		str_to_double(char *str)
{
	double	res;
	double	tmp;
	char	*s;
	int		sign;

	sign = (*str == '-') ? -1 : 1;
	res = (double)ft_atoi(str);
	if ((s = ft_strchr(str, '.')))
	{
		*str == '-' ? ++str : 0;
		while (str != s && ft_isdigit(*str))
			str++;
		if (*str == ',')
			return (res);
		*str == '-' ? error("Incorrect value(minus sign inside double)") : 0;
		if (str == s++)
		{
			(*s >= ',' && *s <= '.') ? error("Incorrect value of double") : 0;
			tmp = (double)ft_atoi(s);
			while (ft_isdigit(*s++))
				tmp /= 10;
			res += tmp * sign;
		}
	}
	return (res);
}

int			str_to_integer(int *num, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit((int)str[i]))
			return (0);
	if (i > 9)
		return (0);
	*num = ft_atoi(str);
	return (1);
}

int			str_to_v3(t_vec3 *vec, char *str)
{
	size_t	len;
	char	*tmp;
	int		i;

	i = -1;
	len = ft_strlen(str);
	if (len < 5 || !is_valid_v3(str) || *str == ',')
		return (0);
	while (++i < 3)
	{
		if (!(tmp = ft_strchr(str, ',')) && i != 2)
			return (0);
		len = (i != 2) ? (size_t)(tmp - str) : ft_strlen(str);
		if (len > 9 || len == 0 || (len == 1 && *str == '.'))
			return (0);
		i == 0 ? vec->x = str_to_double(str) : 0;
		i == 1 ? vec->y = str_to_double(str) : 0;
		i == 2 ? vec->z = str_to_double(str) : 0;
		str = ft_strchr(str, ',');
		i != 2 ? ++str : 0;
		if (i == 2 && str)
			return (0);
	}
	return (1);
}

static int	atoi16(char *num, int char_cnt)
{
	int	digit[2];
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (*num >= '0' && *num <= '9')
			digit[i] = *num - 48;
		else if (*num >= 'A' && *num <= 'F')
			digit[i] = *num - 55;
		else if (*num >= 'a' && *num <= 'f')
			digit[i] = *num - 87;
		else
			digit[i] = 0;
		char_cnt == 2 ? ++num : 0;
	}
	return (16 * digit[0] + digit[1]);
}

int			str_to_rgb(t_color *col, char *str)
{
	size_t	len;

	if (!is_valid_hex(str))
		return (0);
	len = ft_strlen(str);
	if (len == 1)
	{
		col->r = atoi16(str, 1);
		col->g = atoi16(str, 1);
		col->b = atoi16(str, 1);
	}
	else if (len == 3)
	{
		col->r = atoi16(str, 1);
		col->g = atoi16(&str[1], 1);
		col->b = atoi16(&str[2], 1);
	}
	else if (len == 6)
	{
		col->r = atoi16(str, 2);
		col->g = atoi16(&str[2], 2);
		col->b = atoi16(&str[4], 2);
	}
	return (1);
}
