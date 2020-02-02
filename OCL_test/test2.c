/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:17:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/02 15:32:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 268435456 / 2

int	main(void)
{
	double			*a;
	double			*b;
	unsigned int	count;

	count = SIZE;
	if (!(a = (double*)malloc(sizeof(double) * count)))
		return (printf("BAD ALLOCATED A\n"));
	if (!(b = (double*)malloc(sizeof(double) * count)))
		return (printf("BAD ALLOCATED B\n"));
	for (unsigned int i = 0; i < count; ++i)
	{
		a[i] = (double)i;
		b[i] = 0;
	}
	for (unsigned int i = 0; i < count; ++i)
		b[i] = a[i] * a[i] * a[i];
	printf("FINISH\n");
	return (0);
}
