/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:02:05 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:50:22 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	i = 1;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	while (*dst && i++)
		dst++;
	while (*src && (i++ < size))
		*dst++ = *src++;
	*dst = '\0';
	return (len_dst <= size ? (len_dst + len_src) : (size + len_src));
}
