/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:01:44 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 23:45:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	usage(char *app_name)
{
	ft_putstr("Usage: ");
	ft_putstr(app_name);
	ft_putendl(" SOURCE");
	exit(1);
}

int	error(char *err_msg)
{
	if (err_msg)
	{
		ft_putstr("Error: ");
		ft_putendl(err_msg);
	}
	exit(1);
}

int	parse_error(char *err_msg, int line_num)
{
	if (err_msg)
	{
		ft_putstr("ParseError: (");
		ft_putnbr(line_num);
		ft_putstr(") ");
		ft_putendl(err_msg);
	}
	exit(1);
}

int	p_error(char *str)
{
	perror(str);
	exit(1);
}
