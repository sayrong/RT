/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:52:59 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 22:41:42 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_ambient(t_rt *rt, char **split, int line_num)
{
	t_light	*new_l;

	if (!(new_l = (t_light*)malloc(sizeof(t_light))))
		p_error("malloc t_light");
	if (rt->amb_flg)
		parse_error("Should be only one or zero ambient", line_num);
	rt->amb_flg = TRUE;
	if (!split[1] || split[2])
		parse_error("Ambient should have one parameter", line_num);
	if (!is_valid_double(split[1]))
		parse_error("Invalid param: intensity value of the ambient", line_num);
	new_l->intensity = str_to_double(split[1]);
	if (new_l->intensity <= 0 || new_l->intensity > 100)
		parse_error("Range for intensity of the ambient: (0...100]", line_num);
	new_l->intensity /= 100;
	rt->lights = add_new_light(rt->lights, new_l, AMBIENT);
}

void	parse_point(t_rt *rt, char **split, int line_num)
{
	t_light	*new_l;

	if (!(new_l = (t_light*)malloc(sizeof(t_light))))
		p_error("malloc t_light");
	if (!split[1] || !split[2] || split[3])
		parse_error("Point light should have two parameters", line_num);
	if (!str_to_v3(&new_l->position, split[1]))
		parse_error("Invalid param: target point of the point light", line_num);
	if (!is_valid_double(split[2]))
		parse_error("Invalid param: intensity value of the point light",
					line_num);
	new_l->intensity = str_to_double(split[2]);
	if (new_l->intensity <= 0 || new_l->intensity > 100)
		parse_error("Range for intensity of the light: (0...100]", line_num);
	new_l->intensity /= 100;
	rt->lights = add_new_light(rt->lights, new_l, POINT);
}
