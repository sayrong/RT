/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:33:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 21:39:58 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*object(char *name)
{
	ft_printf("%6s%{}s", "", FT_GREEN, name);
	return ("");
}

static char	*field(char *type, char *name, char *end)
{
	ft_printf("%{}s%{s:%{}s%s",
		FT_PURPLE, "|",
		FT_CYAN, type,
		FT_YELLOW, name,
		end);
	return ("");
}

static void	usage_shapes(void)
{
	ft_printf("%4s%{}s\n", "", FT_PURPLE, "# Shapes:");
	ft_printf("%s", object("plane"), field("vec3", "position", ""),
		field("vec3", "rotation", ""), field("hex[136]", "color", ""),
		field("float", "specular", "\n"));
	ft_printf("%s", object("sphere"), field("vec3", "position", ""),
		field("vec3", "rotation", ""), field("float", "radius", ""),
		field("hex[136]", "color", ""), field("float", "specular", "\n"));
	ft_printf("%s", object("cylinder"), field("vec3", "position", ""),
		field("vec3", "rotation", ""), field("float", "radius", ""),
		field("hex[136]", "color", ""), field("float", "specular", "\n"));
	ft_printf("%s", object("cone"), field("vec3", "position", ""),
		field("vec3", "rotation", ""), field("float", "angle", ""),
		field("hex[136]", "color", ""), field("float", "specular", "\n"));
}

void		usage(char *app_name)
{
	ft_printf("%{}s %{}s %{}s\n\n", FT_GREEN, "Usage:",
		FT_YELLOW, app_name, FT_CYAN, "[file_scene]");
	ft_printf("%{}s\n", FT_GREEN, "Parameters types:");
	ft_printf("%4s%{}-10s ex.: 1.1\n", "", FT_BLUE, "[float]");
	ft_printf("%4s%{}-10s ex.: 1.0,-1.0,0.1\n", "", FT_CYAN, "[vec3]");
	ft_printf("%4s%{}-10s ex.: hex1: f, hex3: fff, hex6: ffffff\n\n",
		"", FT_PURPLE, "[hex[136]]");
	ft_printf("%{}s\n", FT_GREEN, "Scene pattern:");
	ft_printf("%4s%{}s", "", FT_PURPLE, "# Here is the comment\n");
	ft_printf("%s%s", object("camera"), field("vec3", "position", ""),
		field("vec3", "rotation", "\n"));
	ft_printf("%4s%{}s\n", "", FT_PURPLE, "# Lights:");
	ft_printf("%s", object("ambient"), field("float", "intensity", "\n"));
	ft_printf("%s", object("point"), field("vec3", "position", ""),
		field("float", "radius", ""), field("float", "intensity", "\n"));
	ft_printf("%s", object("direction"), field("vec3", "direction", ""),
		field("float", "intensity", "\n"));
	usage_shapes();
	exit(0);
}
