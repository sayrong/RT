/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:52:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/16 15:41:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_ambient(t_rt *rt, char **split, int line_num)
{
	t_light	*new_l;

	if (rt->cnt.light == MAX_CNT_LIGHTS)
		parse_error("Max count of lights", line_num);
	if (!(new_l = (t_light*)malloc(sizeof(t_light))))
		p_error("malloc t_light");
	if (rt->flg.amb_flg)
		parse_error("Should be only one or zero ambient", line_num);
	rt->flg.amb_flg = TRUE;
	if (!split[1] || split[2])
		parse_error("Ambient should have one parameter", line_num);
	if (!is_valid_float(split[1]))
		parse_error("Invalid param: intensity value of the ambient", line_num);
	new_l->intensity = str_to_float(split[1]);
	if (new_l->intensity <= 0.0f || new_l->intensity > 1.0f)
		parse_error("Range for intensity of the ambient: (0...1]", line_num);
	rt->lights = add_new_light(rt->lights, new_l, AMBIENT, &rt->cnt.light);
}

void	parse_point(t_rt *rt, char **split, int line_num)
{
	t_light	*new_l;

	if (rt->cnt.light == MAX_CNT_LIGHTS)
		parse_error("Max count of lights", line_num);
	if (!(new_l = (t_light*)malloc(sizeof(t_light))))
		p_error("malloc t_light");
	if (!split[1] || !split[2] || !split[3] || split[4])
		parse_error("Point light should have three parameters", line_num);
	if (!str_to_v3(&new_l->transform.position, split[1]))
		parse_error("Invalid param: position vector of the point light",
					line_num);
	if (!is_valid_float(split[2]))
		parse_error("Invalid param: radius value of the point light", line_num);
	new_l->radius = str_to_float(split[2]);
	if (new_l->radius <= 0 || new_l->radius > 10000)
		parse_error("Range for radius of the point light: (0...10000",
					line_num);
	if (!is_valid_float(split[3]))
		parse_error("Invalid param: intensity of the point light", line_num);
	new_l->intensity = str_to_float(split[3]);
	if (new_l->intensity <= 0 || new_l->intensity > 1000000)
		parse_error("Range for intensity of the point light: (0...1000000]",
			line_num);
	rt->lights = add_new_light(rt->lights, new_l, POINT, &rt->cnt.light);
}

void	parse_direction(t_rt *rt, char **split, int line_num)
{
	t_light	*new_l;

	if (rt->cnt.light == MAX_CNT_LIGHTS)
		parse_error("Max count of lights", line_num);
	if (!(new_l = (t_light*)malloc(sizeof(t_light))))
		p_error("malloc t_light");
	if (!split[1] || !split[2] || split[3])
		parse_error("Direction light should have two parameters", line_num);
	if (!str_to_v3(&new_l->direction, split[1]))
		parse_error("Invalid param: direction vector of the direction light",
					line_num);
	if (!is_valid_float(split[2]))
		parse_error("Invalid param: intensity value of the direction light",
					line_num);
	new_l->intensity = str_to_float(split[2]);
	if (new_l->intensity <= 0.0f || new_l->intensity > 1.0f)
		parse_error("Range for intensity of the direction light: (0...1]",
					line_num);
	rt->lights = add_new_light(rt->lights, new_l, DIRECTION, &rt->cnt.light);
}
