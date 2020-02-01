/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:58:10 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 18:04:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

# define BLACK (t_color){0, 0, 0}


t_color        color_scale(t_color color, double factor)
{
    t_color res;
    
    res.r = color.r * factor;
    res.g = color.g * factor;
    res.b = color.b * factor;
    return (res);
}

t_color        color_add(t_color c1, t_color c2)
{
    t_color color;
    
    color.r = c1.r + c2.r;
    color.g = c1.g + c2.g;
    color.b = c1.b + c2.b;
    return (color);
}

t_color            set_light(t_color *c, double light)
{
    t_color color;
    
    color.r = c->r * light;
    color.g = c->g * light;
    color.b = c->b * light;
    return color;
}

int        get_color_simple(t_color *c)
{
    int    new_red;
    int    new_green;
    int    new_blue;
    
    new_red = c->r;
    new_green = c->g;
    new_blue = c->b;
    return (new_red << 16 | new_green << 8 | new_blue);
}

void init_alias(int *hit, t_color *res, double *light)
{
    *hit = 0;
    *res = BLACK;
    *light = 0;
}

t_color anti_alias(t_inter *inter, int x, int y, t_thread *src)
{
    double    x_y[2];
    t_color    res_tmp[2];
    t_vec2    screen_coord;
    double light_percent;
    int hit;
    
    x_y[0] = x;
    x_y[1] = y;
    init_alias(&hit,&(res_tmp[0]), &light_percent);
    while (x_y[0] < x + 1)
    {
        x_y[1] = y;
        while (x_y[1] < y + 1)
        {
            inter->t = RAY_T_MAX;
            screen_coord = v2_set((2.0 * x_y[0]) / WIDTH - 1.0,
                                  (-2.0 * x_y[1]) / HEIGHT + 1.0);
            set_ray_direction(inter->ray, &screen_coord, &src->rt->cam);
            if (shapeset_intersect(inter, src->rt->shapes))
            {
                light_percent += compute_light(inter, src->rt->shapes, src->rt->lights);
                hit++;
                res_tmp[1] = *(get_color_from_list(inter->shape));
                //n_col = set_light(&n_col,light_percent);
                res_tmp[1] = color_scale(res_tmp[1],0.25);
                res_tmp[0] = color_add(res_tmp[0], res_tmp[1]);
            }
            x_y[1] += 0.5;
        }
        x_y[0] += 0.5;
    }
    light_percent = light_percent / hit;
    return (set_light(&res_tmp[0], light_percent));
    //return (color);
}





t_vec3	get_normal(t_inter *inter)
{
	t_vec3	hit_point;
	t_vec3	tmp;

	tmp = v3_scale(inter->ray->direction, inter->t);
	hit_point = v3_add(inter->ray->origin, tmp);
	if (inter->shape->shape == SPHERE)
		return (get_sphere_normal((t_sphere*)inter->shape->content, hit_point));
	else if (inter->shape->shape == PLANE)
		return (get_plane_normal((t_plane*)inter->shape->content, inter->ray));
	else if (inter->shape->shape == CONE)
		return (get_cone_normal((t_cone*)inter->shape->content, inter->ray,
							hit_point, inter->t));
	else
		return (get_cyl_normal((t_cylinder*)inter->shape->content, inter->ray,
							hit_point, inter->t));
}

int		get_specular(t_inter *inter)
{
	if (inter->shape->shape == SPHERE)
		return ((t_sphere*)inter->shape->content)->specular;
	else if (inter->shape->shape == PLANE)
		return ((t_plane*)inter->shape->content)->specular;
	else if (inter->shape->shape == CONE)
		return ((t_cone*)inter->shape->content)->specular;
	else
		return ((t_cylinder*)inter->shape->content)->specular;
}

void	draw(t_rt *rt)
{
	pthread_t	threads[THREADS_NUM];
	t_thread	data[THREADS_NUM];
	int			i;

	i = -1;
	while (++i < THREADS_NUM)
	{
		data[i].rt = rt;
		data[i].rt_id = i;
		if (pthread_create(threads + i, NULL, calculate, &(data[i])))
			p_error("pthread_create");
	}
	while (i--)
		if (pthread_join(threads[i], NULL))
			p_error("pthread_join");
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
}

void	send_ray(t_inter *inter, int position, t_thread *src)
{
	int		x_y[2];
	//t_vec2	screen_coord;
	int		*cur_pixel;
	//double	light_percent;
	//t_color	*tmp;

	x_y[0] = position % WIDTH;
	x_y[1] = position / HEIGHT;
    
    cur_pixel = get_pixel(x_y[0], x_y[1], src->rt->img);
    t_color col = anti_alias(inter, x_y[0], x_y[1], src);
    *cur_pixel = get_color_simple(&col);
    
//    screen_coord = v2_set((2.0 * x_y[0]) / WIDTH - 1.0,
//                        (-2.0 * x_y[1]) / HEIGHT + 1.0);
//    set_ray_direction(inter->ray, &screen_coord, &src->rt->cam);
//    inter->t = RAY_T_MAX;
//    cur_pixel = get_pixel(x_y[0], x_y[1], src->rt->img);
//    if (shapeset_intersect(inter, src->rt->shapes))
//    {
//        light_percent = compute_light(inter, src->rt->shapes, src->rt->lights);
//        tmp = get_color_from_list(inter->shape);
//        *cur_pixel = get_color(tmp, light_percent);
//    }
//    else
//        *cur_pixel = 0;
}

void	*calculate(void *data)
{
	int			start_end[2];
	t_thread	*src;
	t_ray		r;
	t_inter		inter;

	src = (t_thread *)data;
	start_end[0] = STEP * src->rt_id;
	start_end[1] = (src->rt_id == THREADS_NUM - 1) ?
					HEIGHT * WIDTH : start_end[0] + STEP;
	r.origin = src->rt->cam.origin;
	r.t_max = RAY_T_MAX;
	inter_new_ray(&inter, &r);
	while (start_end[0] < start_end[1])
	{
		send_ray(&inter, start_end[0], src);
		start_end[0]++;
	}
	return (NULL);
}
