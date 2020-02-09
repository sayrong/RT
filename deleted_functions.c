/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleted_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 12:56:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 18:00:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//no_hook
static int	no_hook(void *param)
{
	t_rt	*rt;
	t_vec3	step;

	rt = (t_rt*)param;
	if (rt->play)
	{
		step = v3_sub(rt->cam.origin, rt->cam.target);
		step = v3_rot_y(step, ANGLE);
		rt->cam.origin = v3_add(rt->cam.target, step);
		rt->cam = camera_new(rt->cam.origin, rt->cam.target);
		draw(rt);
	}
	return (0);
}


//deal_key.c
static _Bool	is_move(int key)
{
	return (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY ||
			key == Q_KEY || key == E_KEY);
}

static _Bool	is_shape_move(int key)
{
	return (key == UP || key == DOWN || key == LEFT || key == RIGHT ||
			key == R_SHIFT || key == R_CTRL);
}

static _Bool	is_rotate(int key)
{
	return (key == TWO_NUM || key == FOUR_NUM || key == SIX_NUM ||
			key == EIGHT_NUM);
}

static void		move_cam(t_cam *cam, int key)
{
	t_vec3	step;
	double	move;

	move = (key == W_KEY || key == D_KEY || key == E_KEY) ? MOVE : -MOVE;
	step = v3_sub(cam->target, cam->origin);
	if (key == A_KEY || key == D_KEY)
		step = v3_cross(step, cam->up);
	else if (key == Q_KEY || key == E_KEY)
		step = v3_cross(step, cam->right);
	step = v3_scale(step, move);
	cam->origin = v3_add(cam->origin, step);
	cam->target = v3_add(cam->target, step);
	*cam = camera_new(cam->origin, cam->target);
}

static void		move_shape(t_list_shape *shape, int key, t_cam *cam)
{
	t_vec3	step;
	double	move;

	move = (key == UP || key == RIGHT || key == R_CTRL) ? MOVE : -MOVE;
	step = v3_sub(cam->target, cam->origin);
	if (key == LEFT || key == RIGHT)
		step = v3_cross(step, cam->up);
	else if (key == R_SHIFT || key == R_CTRL)
		step = v3_cross(step, cam->right);
	step = v3_scale(step, move);
	if (shape->shape == SPHERE)
		((t_sphere*)shape->content)->center =
			v3_add(((t_sphere*)shape->content)->center, step);
	else if (shape->shape == CYLINDER)
		((t_cylinder*)shape->content)->position =
			v3_add(((t_cylinder*)shape->content)->position, step);
	else if (shape->shape == CONE)
		((t_cone*)shape->content)->position =
			v3_add(((t_cone*)shape->content)->position, step);
	else if (shape->shape == PLANE)
		((t_plane*)shape->content)->position =
			v3_add(((t_plane*)shape->content)->position, step);
}

static void		rotate_cam(t_cam *cam, int key)
{
	t_vec3	step;
	double	angle;

	angle = (key == EIGHT_NUM || key == SIX_NUM) ? -ANGLE : ANGLE;
	step = v3_sub(cam->target, cam->origin);
	if (key == SIX_NUM || key == FOUR_NUM)
		step = v3_rot_y(step, angle);
	else if (key == TWO_NUM || key == EIGHT_NUM)
		step = v3_rot_x(step, angle);
	cam->target = v3_add(cam->origin, step);
	*cam = camera_new(cam->origin, cam->target);
}

int				deal_key(int key, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if (key == ESC)
		red_x_button(param);
	if (key == P_KEY)
		rt->play ^= TRUE;
	else if (key == M_KEY)
		rt->is_anti_alias = !rt->is_anti_alias;
	else if (key == C_KEY && rt->marker)
		rt->is_rgb ^= TRUE;
	else if (is_move(key))
		move_cam(&rt->cam, key);
	else if (is_rotate(key))
		rotate_cam(&rt->cam, key);
	else if (rt->marker && is_shape_move(key))
		move_shape(rt->marker, key, &rt->cam);
	else
		return (0);
	draw(rt);
	return (0);
}


//mouse_click
static void	middle_button(t_rt *rt, t_list_shape *shape)
{
	t_list_shape	*tmp;

	if (shape->marker == TRUE)
		rt->marker = NULL;
	if (rt->shapes == shape)
		rt->shapes = rt->shapes->next;
	else
	{
		tmp = rt->shapes;
		while (tmp->next != shape)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	del_shape(&shape);
	draw(rt);
}

static void	left_middle_button(t_rt *rt, int button, int x, int y)
{
	t_ray			r;
	t_inter			inter;
	t_vec2			screen_coord;

	screen_coord = v2_set((2.0 * x) / WIDTH - 1.0, (-2.0 * y) / HEIGHT + 1.0);
	r.origin = rt->cam.origin;
	r.t_max = RAY_T_MAX;
	inter_new_ray(&inter, &r);
	set_ray_direction(inter.ray, &screen_coord, &rt->cam);
	if (shapeset_intersect(&inter, rt->shapes))
	{
		if (button == SCROLL_CLICK)
			return (middle_button(rt, inter.shape));
		inter.shape->marker ^= 1;
		if (!rt->marker)
			rt->marker = inter.shape;
		else if (rt->marker->marker == FALSE)
			rt->marker = NULL;
		else
		{
			rt->marker->marker = FALSE;
			rt->marker = inter.shape;
		}
		draw(rt);
	}
}

static void	scrolling(t_rt *rt, int button)
{
	t_shape_type	type;
	void			*shape;

	type = rt->marker->shape;
	shape = rt->marker->content;
	if (button == 4)
	{
		if (type == SPHERE)
			((t_sphere*)shape)->radius += 1;
		else if (type == CYLINDER)
			((t_cylinder*)shape)->radius += 1;
		else if (type == CONE && ((t_cone*)shape)->angle + 10 < 180)
			((t_cone*)shape)->angle += 10;
		else
			return ;
	}
	else if (type == SPHERE && ((t_sphere*)shape)->radius - 1 > 0)
		((t_sphere*)shape)->radius -= 1;
	else if (type == CYLINDER && ((t_cylinder*)shape)->radius - 1 > 0)
		((t_cylinder*)shape)->radius -= 1;
	else if (type == CONE && ((t_cone*)shape)->angle - 10 > 0)
		((t_cone*)shape)->angle -= 10;
	else
		return ;
	draw(rt);
}

static void	set_shape_color(t_rt *rt, t_color *shape_color, int *pixel)
{
	*shape_color = (t_color){(*pixel & 0xFF0000) >> 16,
							(*pixel & 0xFF00) >> 8,
							*pixel & 0xFF};
	rt->is_rgb = FALSE;
	draw(rt);
}

int			mouse_move(int x, int y, void *param)
{
	t_rt	*rt;
	int		pixel;

	rt = (t_rt*)param;
	if (!rt->is_move || !rt->marker || !rt->is_rgb ||
			x < 0 || x >= 100 || y < 0 || y >= 100)
		return (0);
	pixel = *get_pixel(x, y, rt->rgb_spectrum);
	*get_color_from_list(rt->marker) = (t_color){(pixel & 0xFF0000) >> 16,
												(pixel & 0xFF00) >> 8,
												pixel & 0xFF};
	draw(rt);
	return (0);
}

int			mouse_release(int button, int x, int y, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if (!rt->is_move || button != 1)
		return (0);
	++x;
	++y;
	rt->is_move = FALSE;
	rt->is_rgb = FALSE;
	draw(rt);
	return (0);
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_rt	*rt;

	rt = (t_rt*)param;
	if ((button != 1 && !rt->marker) && button != SCROLL_CLICK)
		return (0);
	if (button == 1 && rt->marker && rt->is_rgb &&
			x >= 0 && x < 100 && y >= 0 && y < 100)
	{
		rt->is_move = TRUE;
		mouse_move(x, y, param);
	}
	else if (button == 1 && rt->marker && rt->is_rgb &&
			x >= 0 && x < 100 && y >= 0 && y < 100)
		set_shape_color(rt, get_color_from_list(rt->marker),
						get_pixel(x, y, rt->rgb_spectrum));
	else if (button == 1 || button == SCROLL_CLICK)
		left_middle_button(rt, button, x, y);
	else if (button == 4 || button == 5)
		scrolling(rt, button);
	return (0);
}

//draw
void	draw(t_rt *rt)
{
	if (rt->marker == NULL)
		rt->flg.is_rgb = FALSE;
	calculate();
	if (rt->flg.is_rgb)
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
