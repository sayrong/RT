/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:15:02 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/15 21:05:11 by cschoen          ###   ########.fr       */
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
# define MOVE 0.02
# define ANGLE 2
# define MAX_CNT_LIGHTS 32
# define MAX_CNT_SHAPES 64
# define BUFFER_BYTES 13050
# define SHADER_RT_FILE "./shader/obj/rt.frag"

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <mlx.h>
# include <pthread.h>
# include "../libvec/inc/libvec.h"
# include "../libft/inc/libft.h"
# include "macoskeys.h"

typedef struct			s_color
{
	float				r;
	float				g;
	float				b;
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

typedef enum			e_light_type
{
	AMBIENT,
	POINT,
	DIRECTION,
	CNT_OF_TYPES
}						t_light_type;

typedef struct			s_light
{
	t_light_type		type;
	t_transform			transform;
	t_vec3				direction;
	float				intensity;
	float				radius;
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
	_Bool				marker;
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
	t_transform			transform;
	t_vec3				direction;
	// double				h;
	// double				w;
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
	t_img				*img;
	t_img				*rgb_spectrum;
}						t_mlx;

typedef struct			s_flag
{
	_Bool				cam_flg;
	_Bool				amb_flg;
	_Bool				play;
	_Bool				is_anti_alias;
	_Bool				is_rgb;
	_Bool				is_move;
}						t_flag;

typedef struct			s_rt
{
	t_gl				gl;
	t_mlx				mlx;
	t_flag				flg;
	t_cam				cam;
	t_list_shape		*shapes;
	t_list_shape		*marker;
	t_list_light		*lights;
	int					shapes_cnt;
	int					lights_cnt;
}						t_rt;

void					usage(char *app_name);
int						error(char *err_msg);
int						p_error(char *err_msg);
int						parse_error(char *err_msg, int line_num);

void					del_shape(t_list_shape **shape);

int						is_valid_whitespaces(char *str);
int						is_valid_v3(char *str);
int						is_valid_double(char *str);
int						is_valid_hex(char *str);

double					str_to_double(char *str);
int						str_to_integer(int *num, char *str);
int						str_to_v3(t_vec3 *vec, char *str);
int						str_to_rgb(t_color *col, char *str);

void					gl_init(t_rt *rt);
void					callback_key(GLFWwindow *window, int key, int scancode,
											int action);
void					callback_mouse_button(GLFWwindow *window, int key,
											int action, int mode);
void					callback_cursor_position(GLFWwindow *window,
											double xpos, double ypos);
char					*combine_str_int_str(char *str1, int number,
											char *str2);
void					set_settings(t_rt *rt, GLuint shader_program);
void					set_uniform_shape(t_list_shape *shape, int index,
											GLuint shader_program);

void					parse_ambient(t_rt *rt, char **split, int line_num);
void					parse_point(t_rt *rt, char **split, int line_num);
void					parse_shape(t_rt *rt, char **split, int line_num);
void					parser(t_rt *rt, int fd);

void					make_rgb_spectrum(char *data);

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
									t_shape_type type, int *counter);

t_list_light			*new_light_list(t_light *light, t_light_type type);
t_list_light			*add_new_light(t_list_light *list, t_light *light,
									t_light_type type, int *counter);

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


void					*calculate(void *data);
void					draw(t_rt *rt);

t_color					color_add(t_color c1, t_color c2);

#endif
