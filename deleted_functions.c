/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleted_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 12:56:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 02:22:48 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	no_hook(void *param)
{
	t_rt	*rt;
	t_vec3	step;

	rt = (t_rt*)param;
	if (rt->flg.play)
	{
		step = v3_sub(rt->cam.origin, rt->cam.target);
		step = v3_rot_y(step, ANGLE);
		rt->cam.origin = v3_add(rt->cam.target, step);
		rt->cam = camera_new(rt->cam.origin, rt->cam.target);
		draw(rt);
	}
	return (0);
}


//draw
void	draw(t_rt *rt)
{
	if (rt->marker == NULL)
		rt->flg.open_spectrum = FALSE;
	calculate();
	if (rt->flg.open_spectrum)
	{
		//put spectrum
	}
}


//cross pixel and left_mouse_button in shader
	i = glGetUniformLocation(shader_program, "del");
	glUniform2f(i, (GLfloat)(rtv1->del_mouse_pos_x * 2),
					(GLfloat)((1080 - rtv1->del_mouse_pos_y) * 2));


//another
void					send_ray(t_inter *inter, int position, t_thread *src);
int						anti_aliasing(t_inter *inter, int *xy, t_thread *src, double incrementer);

void	init_aliasing(double *tmp_xy, int *xy, double *light, int *hit)
{
	tmp_xy[0] = xy[0];
	tmp_xy[1] = xy[1];
	*light = 0;
	*hit = 0;
}
