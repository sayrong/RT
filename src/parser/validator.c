/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:23:24 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/12 20:47:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_valid_whitespaces(char *str)
{
	while (*str)
	{
		if (*str == ' ' || (*str >= '\t' && *str <= '\r'))
			return (0);
		++str;
	}
	return (1);
}

int	is_valid_v3(char *str)
{
	int		i;
	int		comma;
	_Bool	dot;
	_Bool	minus;

	i = -1;
	comma = 0;
	dot = FALSE;
	minus = FALSE;
	while (str[++i])
	{
		if (str[i] < ',' && str[i] > '.' && !ft_isdigit(str[i]))
			return (0);
		str[i] == '.' && dot == TRUE ? error("Incorrect value of double") : 0;
		str[i] == '.' ? dot = TRUE : 0;
		str[i] == '-' && minus == TRUE ? error("Incorrect value of double") : 0;
		str[i] == '-' && dot == TRUE ? error("Incorrect value of double") : 0;
		str[i] == '-' ? minus = TRUE : 0;
		str[i] == ',' ? dot = FALSE : 0;
		str[i] == ',' ? minus = FALSE : 0;
		str[i] == ',' ? ++comma : 0;
		if (str[i] == ',' && comma > 2)
			error("Incorrect vector params: more than 2 commas");
	}
	return (1);
}

int	is_valid_double(char *str)
{
	int		i;
	_Bool	dot;
	size_t	len;

	i = -1;
	len = ft_strlen(str);
	dot = FALSE;
	if (len < 1 || len > 9 || (len == 1 && (!ft_isdigit(str[0]))))
		return (0);
	if (str[0] == '-')
		++i;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		if (str[i] == '.' && dot == TRUE)
			return (0);
		str[i] == '.' ? dot = TRUE : 0;
	}
	return (1);
}

int	is_valid_hex(char *str)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(str);
	if (len != 6 && len != 3 && len != 1)
		return (0);
	while (str[++i])
	{
		str[i] = ft_tolower(str[i]);
		if (!ft_isdigit(str[i]) && (str[i] < 'a' || str[i] > 'f'))
			return (0);
	}
	return (1);
}
