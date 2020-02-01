/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:53:44 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/31 19:35:31 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s && *s++ != c)
		num++;
	return (num);
}

static t_list	*ft_lstcreate(t_list *elem, char const *s, char c)
{
	while (*s && *s == c)
		s++;
	if (*s)
	{
		elem = ft_lstnew(ft_strsub(s, 0, ft_len(s, c)), ft_len(s, c) + 1);
		if (elem == NULL)
			return (NULL);
		while (*s && *s != c)
			s++;
		elem->next = ft_lstcreate(elem->next, s, c);
		if (elem->next == NULL)
		{
			free(elem->content);
			free(elem);
			return (NULL);
		}
	}
	else
	{
		if ((elem = ft_lstnew(NULL, 0)) == NULL)
			return (NULL);
	}
	return (elem);
}

t_list			*ft_lstsplit(char const *s, char c)
{
	t_list	*elem;

	elem = NULL;
	if (s == NULL)
		return (NULL);
	elem = ft_lstcreate(elem, s, c);
	return (elem);
}
