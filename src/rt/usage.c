/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:33:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 20:29:02 by cschoen          ###   ########.fr       */
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
	ft_printf("%s", field("float", "specular", "\n"),
		field("hex[136]", "color", ""), field("vec3", "rotation", ""),
		field("vec3", "position", ""), object("plane"));
	ft_printf("%s", field("float", "specular", "\n"),
		field("hex[136]", "color", ""), field("float", "radius", ""),
		field("vec3", "rotation", ""), field("vec3", "position", ""),
		object("sphere"));
	ft_printf("%s", field("float", "specular", "\n"),
		field("hex[136]", "color", ""), field("float", "radius", ""),
		field("vec3", "rotation", ""), field("vec3", "position", ""),
		object("cylinder"));
	ft_printf("%s", field("float", "specular", "\n"),
		field("hex[136]", "color", ""), field("float", "angle", ""),
		field("vec3", "rotation", ""), field("vec3", "position", ""),
		object("cone"));
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
	ft_printf("%s%s", field("vec3", "rotation", "\n"),
		field("vec3", "position", ""),
		object("camera"));
	ft_printf("%4s%{}s\n", "", FT_PURPLE, "# Lights:");
	ft_printf("%s", field("float", "intensity", "\n"),
		object("ambient"));
	ft_printf("%s", field("float", "intensity", "\n"),
		field("float", "radius", ""), field("vec3", "position", ""),
		object("point"));
	ft_printf("%s", field("float", "intensity", "\n"),
		field("vec3", "direction", ""),
		object("direction"));
	usage_shapes();
	exit(0);
}
