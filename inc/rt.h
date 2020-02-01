/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:15:02 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/14 23:36:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define RAY_T_MIN 1e-4
# define RAY_T_MAX 1e30

# define TRUE 1
# define FALSE 0
# define WIDTH 800
# define HEIGHT 800
# define PI 3.14159265359
# define THREADS_NUM 8
# define STEP (WIDTH * HEIGHT) / THREADS_NUM
# define MOVE 0.02
# define ANGLE 2

# include <mlx.h>
# include <pthread.h>
# include "../libvec/inc/libvec.h"
# include "../libft/inc/libft.h"
# include <stdio.h>
# include "macoskeys.h"

/*
** # include "linuxkeys.h"
*/

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef enum			e_light_type
{
	AMBIENT,
	POINT
}						t_light_type;

typedef struct			s_light
{
	t_light_type		type;
	double				intensity;
	t_vec3				position;
	t_vec3				target;
}						t_light;

typedef enum			e_shape_type
{
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CNT_OF_TYPES
}						t_shape_type;

typedef struct			s_list_shape
{
	void				*content;
	t_shape_type		shape;
	struct s_list_shape	*next;
}						t_list_shape;

typedef struct			s_list_light
{
	t_light				*light;
	t_light_type		type;
	struct s_list_light	*next;
}						t_list_light;

typedef struct			s_ray
{
	t_vec3				origin;
	t_vec3				direction;
	double				t_max;
}						t_ray;

typedef struct			s_plane
{
	t_vec3				position;
	t_vec3				normal;
	t_shape_type		shape;
	t_color				color;
	int					specular;
}						t_plane;

typedef struct			s_sphere
{
	t_vec3				center;
	double				radius;
	t_shape_type		shape;
	t_color				color;
	int					specular;
}						t_sphere;

typedef struct			s_cone
{
	t_vec3				position;
	t_vec3				dir;
	double				angle;
	t_color				color;
	t_shape_type		shape;
	int					specular;
}						t_cone;

typedef struct			s_cylinder
{
	t_vec3				position;
	t_vec3				dir;
	double				radius;
	t_color				color;
	t_shape_type		shape;
	int					specular;
}						t_cylinder;

typedef struct			s_intersection
{
	t_ray				*ray;
	double				t;
	t_list_shape		*shape;
}						t_inter;

typedef struct			s_camera
{
	double				h;
	double				w;
	t_vec3				origin;
	t_vec3				target;
	t_vec3				forward;
	t_vec3				up;
	t_vec3				right;
	t_vec3				upguide;
}						t_cam;

typedef struct			s_img
{
	void				*img_ptr;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct			s_rt
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				*img;
	t_cam				cam;
	t_list_shape		*shapes;
	t_list_light		*lights;
	_Bool				cam_flg;
	_Bool				amb_flg;
	_Bool				play;
}						t_rt;

typedef struct			s_thread
{
	t_rt				*rt;
	int					rt_id;
	int					y_min;
	int					y_max;
}						t_thread;

int						usage(char *app_name);
int						error(char *err_msg);
int						p_error(char *err_msg);
int						parse_error(char *err_msg, int line_num);

int						is_valid_whitespaces(char *str);
int						is_valid_v3(char *str);
int						is_valid_double(char *str);
int						is_valid_hex(char *str);

double					str_to_double(char *str);
int						str_to_integer(int *num, char *str);
int						str_to_v3(t_vec3 *vec, char *str);
int						str_to_rgb(t_color *col, char *str);

void					parse_ambient(t_rt *rt, char **split, int line_num);
void					parse_point(t_rt *rt, char **split, int line_num);
void					parse_shape(t_rt *rt, char **split, int line_num);
void					parser(char *source, t_rt *rt, int fd, int line_num);

t_img					*img_new(int width, int height, t_rt *rt);
int						*get_pixel(int x, int y, t_img *img);

t_cam					camera_new(t_vec3 origin, t_vec3 target);
t_plane					*plane_new(t_vec3 position, t_vec3 normal, int spec);
t_sphere				*sphere_new(t_vec3 center, double radius, int spec);
t_cylinder				*cylinder_new(t_vec3 position, t_vec3 direction,
									double r, int spec);
t_cone					*cone_new(t_vec3 position, t_vec3 direction,
									double angle, int spec);

t_vec3					get_plane_normal(t_plane *plane, t_ray *ray);
t_vec3					get_sphere_normal(t_sphere *sphere, t_vec3 hit_point);
t_vec3					get_cyl_normal(t_cylinder *cyl, t_ray *ray,
									t_vec3 hit_point, double t);
t_vec3					get_cone_normal(t_cone *cone, t_ray *ray,
									t_vec3 hit_point, double t);

t_list_shape			*new_shape_list(void *content, t_shape_type type);
t_list_shape			*add_new_shape(t_list_shape *list, void *content,
									t_shape_type type);

t_list_light			*new_light_list(t_light *light, t_light_type type);
t_list_light			*add_new_light(t_list_light *list, t_light *light,
									t_light_type type);

void					inter_new_ray(t_inter *inter, t_ray *ray);
void					set_ray_direction(t_ray *r, t_vec2 *point, t_cam *cam);

double					compute_light(t_inter *inter, t_list_shape *scene,
									t_list_light *lights);

t_vec3					get_normal(t_inter *inter);
int						get_specular(t_inter *inter);
double					degrees_to_rad(double angle_in_degrees);
int						define_t(double t1, double t2, t_inter *inter,
									t_list_shape *shape_in_list);

_Bool					plane_intersect(t_inter *inter,
									t_list_shape *shape_in_list);
_Bool					sphere_intersect(t_inter *inter,
									t_list_shape *shape_in_list);
_Bool					cone_intersect(t_inter *inter,
									t_list_shape *shape_in_list);
_Bool					cylinder_intersect(t_inter *inter,
									t_list_shape *shape_in_list);

_Bool					shape_intersect(t_inter *inter, t_list_shape *shape);
_Bool					shapeset_intersect(t_inter *inter,
									t_list_shape *shape_list);

void					white(t_color *color);
int						get_color(t_color *c, double light);
t_color					*get_color_from_list(t_list_shape *list);

void					send_ray(t_inter *inter, int position, t_thread *src);
void					*calculate(void *data);
void					draw(t_rt *rt);

int						red_x_button(void *param);
int						deal_key(int key, void *param);

#endif
