/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:15:02 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/17 06:16:34 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define RAY_T_MIN 1.175494351e-38
# define RAY_T_MAX 3.402823466e+38

# define TRUE 1
# define FALSE 0
# define WIDTH 1000
# define HEIGHT 1000
# define SPECTRUM_W 248
# define UI_W 500
# define UI_H 800
# define PI 3.14159265359
# define MOVE 0.02
# define ANGLE 2
# define MAX_CNT_LIGHTS 30
# define MAX_CNT_SHAPES 30
# define BUFFER_BYTES 13050
# define SHADER_RT_FILE "./shader/obj/rt.frag"

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <mlx.h>
# include "../libvec/inc/libvec.h"
# include "../libft/inc/libft.h"
# include "macoskeys.h"

typedef enum			e_light_type
{
	AMBIENT,
	POINT,
	DIRECTION,
	CNT_OF_TYPES_L
}						t_light_type;

typedef enum			e_shape_type
{
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CNT_OF_TYPES
}						t_shape_type;

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef	struct			s_material
{
	t_color				color;
	float				specular;
}						t_material;

typedef	struct			s_transform
{
	t_vec3				position;
	t_vec3				rotation;
}						t_transform;

typedef struct			s_light
{
	t_light_type		type;
	t_transform			transform;
	t_vec3				direction;
	float				intensity;
	float				radius;
}						t_light;

typedef struct			s_list_light
{
	t_light_type		type;
	t_light				*light;
	struct s_list_light	*next;
}						t_list_light;

typedef struct			s_plane
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
}						t_plane;

typedef struct			s_sphere
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
}						t_sphere;

typedef struct			s_cone
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				angle;
}						t_cone;

typedef struct			s_cylinder
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
}						t_cylinder;

typedef struct			s_list_shape
{
	t_shape_type		type;
	void				*shape;
	_Bool				marker;
	struct s_list_shape	*next;
}						t_list_shape;

typedef struct			s_ray
{
	t_vec3				origin;
	t_vec3				direction;
	float				t_max;
}						t_ray;

typedef struct			s_intersection
{
	t_ray				ray;
	float				t;
	t_list_shape		*shape;
}						t_inter;

typedef struct			s_camera
{
	t_transform			transform;
	t_vec3				direction;
	// float				h;
	// float				w;
	// t_vec3				origin;
	// t_vec3				target;
	// t_vec3				forward;
	// t_vec3				up;
	// t_vec3				right;
	// t_vec3				upguide;
}						t_cam;

typedef struct			s_gl
{
	char				*vertex_shader_source;
	char				*fragment_shader_source;
	GLFWwindow			*window;
	GLuint				fragment_shader;
	GLuint				vertex_shader;
	GLuint				shader_program;
	GLuint				vbo;
	GLuint				vao;
	GLuint				ebo;
}						t_gl;

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

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				*rgb;
}						t_mlx;

typedef struct			s_flag
{
	_Bool				cam_flg;	//в сцене есть камера
	_Bool				amb_flg;	//в сцене есть свет
	_Bool				play;		//работает но_хук для кручения
	_Bool				run;		//обновляет openGL win
	_Bool				is_anti_alias;	//вкл/выкл анти альяс
	_Bool				hold_rmb_ogl;	//hold RIGHT MOUSE BUTTON OGL
	_Bool				hold_lmb_mlx;	//hold LEFT MOUSE BUTTON MLX
	_Bool				put_ui;			//создать окно ui
	_Bool				open_ui;		//открыто окно ui
}						t_flag;

typedef struct			s_counter
{
	int					light;
	int					plane;
	int					sphere;
	int					cone;
	int					cylinder;
}						t_counter;

typedef struct			s_rt
{
	t_gl				gl;
	t_mlx				mlx;
	t_flag				flg;
	t_cam				cam;
	t_list_shape		*marker;
	t_list_shape		*shapes;
	t_list_light		*lights;
	t_counter			cnt;
	double				mouse_x;
	double				mouse_y;
}						t_rt;

void					usage(char *app_name);
int						error(char *err_msg);
int						p_error(char *err_msg);
int						parse_error(char *err_msg, int line_num);

void					del_shape(t_list_shape **shape, t_counter *cnt);

int						is_valid_whitespaces(char *str);
int						is_valid_v3(char *str);
int						is_valid_float(char *str);
int						is_valid_hex(char *str);

float					str_to_float(char *str);
int						str_to_integer(int *num, char *str);
int						str_to_v3(t_vec3 *vec, char *str);
int						str_to_rgb(t_color *col, char *str);

void					init_ogl(t_rt *rt);
void					init_mlx(t_rt *rt);
void					callback_key(GLFWwindow *window, int key, int scancode,
											int action);
void					callback_mouse_button(GLFWwindow *window, int key,
											int action, int mode);
void					callback_cursor_position(GLFWwindow *window,
											float xpos, float ypos);
char					*combine_str_int_str(char *str1, int number,
											char *str2);
float					clamp(float number, float min, float max);
void					set_settings(t_rt *rt, GLuint shader_program);
void					set_uniform_light(t_light *light, int index,
											GLuint shader_program);
void					set_uniform_shape(t_list_shape *shape, int index,
										GLuint shader_program, _Bool marker);
void					set_uniform_plane(t_plane *shape, int index,
										GLuint shader_program, _Bool marker);
void					set_uniform_sphere(t_sphere *shape, int index,
										GLuint shader_program, _Bool marker);
void					set_uniform_cylinder(t_cylinder *shape, int index,
										GLuint shader_program, _Bool marker);
void					set_uniform_cone(t_cone *shape, int index,
										GLuint shader_program, _Bool marker);

void					parse_ambient(t_rt *rt, char **split, int line_num);
void					parse_point(t_rt *rt, char **split, int line_num);
void					parse_direction(t_rt *rt, char **split, int line_num);
void					parse_shape(t_rt *rt, char **split, int line_num);
void					parser(t_rt *rt, int fd);

void					make_rgb_spectrum(char *data);

t_cam					camera_new(t_vec3 origin, t_vec3 target);
t_plane					*plane_new(t_transform *transform,
									t_material *material);
t_sphere				*sphere_new(t_transform *transform,
									t_material *material, float radius);
t_cylinder				*cylinder_new(t_transform *transform,
									t_material *material, float radius);
t_cone					*cone_new(t_transform *transform,
									t_material *material, float angle);

t_vec3					get_plane_normal(t_plane *plane, t_ray *ray);
t_vec3					get_sphere_normal(t_sphere *sphere, t_vec3 hit_point);
t_vec3					get_cyl_normal(t_cylinder *cyl, t_ray *ray,
									t_vec3 hit_point, float t);
t_vec3					get_cone_normal(t_cone *cone, t_ray *ray,
									t_vec3 hit_point, float t);

t_list_shape			*new_shape_list(void *shape, t_shape_type type);
t_list_shape			*add_new_shape(t_list_shape *list, void *shape,
									t_shape_type type, int *counter);

t_list_light			*new_light_list(t_light *light, t_light_type type);
t_list_light			*add_new_light(t_list_light *list, t_light *light,
									t_light_type type, int *counter);

void					inter_new_ray(t_inter *inter, t_ray *ray);
void					set_ray_direction(t_ray *r, t_vec2 *point, t_cam *cam);

float					compute_light(t_inter *inter, t_list_shape *scene,
									t_list_light *lights);

t_vec3					get_normal(t_inter *inter);
int						get_specular(t_inter *inter);
float					degrees_to_rad(float angle_in_degrees);
int						define_t(float t1, float t2, t_inter *inter,
									t_list_shape *shape_in_list);

_Bool					plane_intersect(t_inter *inter,
									t_list_shape *shape_in_list);
_Bool					sphere_intersect(t_inter *inter,
									t_list_shape *shape_in_list);
_Bool					cone_intersect(t_inter *inter,
									t_list_shape *shape_in_list, t_cone *cone);
_Bool					cylinder_intersect(t_inter *inter,
									t_list_shape *shape_in_list);

_Bool					shape_intersect(t_inter *inter, t_list_shape *shape);
_Bool					shapeset_intersect(t_inter *inter,
									t_list_shape *shape_list);

void					white(t_color *color);
int						get_color(t_color *c, float light);
t_color					*get_color_from_list(t_list_shape *list);

void					mlx_run(t_rt *rt);
void					run(t_rt *rt);

t_color					color_add(t_color c1, t_color c2);
t_img					*new_img(int width, int height, t_rt *rt);
int						red_x_button(void *param);
int						no_hook(void *param);
void					input_hook(t_rt *rt);
int						deal_key(int key, void *param);
void					init_ray(t_inter *inter, t_vec2 *mouse_pos, t_cam *cam);

#endif
