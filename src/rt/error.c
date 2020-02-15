/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:01:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 15:33:59 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	error(char *err_msg)
{
	if (err_msg)
		ft_printf("Error: %s\n", err_msg);
	exit(1);
}

int	parse_error(char *err_msg, int line_num)
{
	if (err_msg)
		ft_printf("ParseError: (%d) %s\n", line_num, err_msg);
	exit(1);
}

int	p_error(char *str)
{
	perror(str);
	exit(1);
}
