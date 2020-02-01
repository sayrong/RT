/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:59:35 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/08 22:04:41 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 9 || n < -9)
		ft_putnbr_fd(n / 10, fd);
	if (n > -10 && n < 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd(ft_abs(n % 10) + '0', fd);
}
