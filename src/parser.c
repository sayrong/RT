/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:17:56 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 22:41:16 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	del_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
}

static void	check_mistakes(t_rt *rt)
{
	!rt->cam_flg ? error("Camera is not initialized") : 0;
	!rt->shapes ? error("Scene without shapes") : 0;
	!rt->lights ? error("Scene without light") : 0;
}

static void	parse_cam(t_rt *rt, char **split, int line_num)
{
	t_vec3	origin;
	t_vec3	target;

	if (rt->cam_flg)
		parse_error("Should be only one camera on the scene", line_num);
	rt->cam_flg = TRUE;
	if (!split[1] || !split[2] || split[3])
		parse_error("Camera should have two parameters", line_num);
	if (!str_to_v3(&origin, split[1]))
		parse_error("Invalid param: position vector of the camera", line_num);
	if (!str_to_v3(&target, split[2]))
		parse_error("Invalid param: target point of the camera", line_num);
	if (origin.x == target.x && origin.y == target.y && origin.z == target.z)
		parse_error("Position and target must have different values",
					line_num);
	if (v3_length(v3_sub(origin, target)) <= 1)
		parse_error("Lenght between position and target must be greater than 1",
					line_num);
	rt->cam = camera_new(origin, target);
}

static void	parse_split(char **split, t_rt *rt, int line_num)
{
	size_t	len;
	size_t	i;

	i = -1;
	len = ft_strlen(split[0]);
	while (++i < len)
		split[0][i] = ft_tolower(split[0][i]);
	if (ft_strequ(split[0], "camera"))
		parse_cam(rt, split, line_num);
	else if (ft_strequ(split[0], "ambient"))
		parse_ambient(rt, split, line_num);
	else if (ft_strequ(split[0], "point"))
		parse_point(rt, split, line_num);
	else if (ft_strequ(split[0], "plane") || ft_strequ(split[0], "sphere") ||
			ft_strequ(split[0], "cylinder") || ft_strequ(split[0], "cone"))
		parse_shape(rt, split, line_num);
	else
		parse_error("Unknown string", line_num);
	del_split(split);
}

void		parser(char *source, t_rt *rt, int fd, int line_num)
{
	int		res;
	char	*line;
	char	*trim;
	char	**split;

	(fd = open(source, O_RDONLY)) < 0 ? p_error("Can't open the file") : 0;
	line = NULL;
	while ((res = get_next_line(fd, &line)) && ++line_num)
	{
		res < 0 ? p_error("Reading error") : 0;
		!(trim = ft_strtrim(line)) ? p_error("ft_strtrim") : ft_strdel(&line);
		(*trim == '#' || *trim == '\0') ? ft_strdel(&trim) : 0;
		if (!trim)
			continue ;
		if (!is_valid_whitespaces(trim))
			parse_error("No whitespaces in params", line_num);
		!(split = ft_strsplit(trim, '|')) ? p_error("ft_strsplit") : 0;
		!split[0] ? parse_error("Unknown string", line_num) : 0;
		ft_strdel(&trim);
		parse_split(split, rt, line_num);
	}
	close(fd);
	check_mistakes(rt);
}
