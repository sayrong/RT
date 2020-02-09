/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 11:56:32 by cschoen           #+#    #+#             */
/*   Updated: 2020/02/09 18:04:44 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_window(t_rt *rt)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	rt->gl.window = glfwCreateWindow(WIDTH, HEIGHT, "RT", NULL, NULL);
	if (rt->gl.window == NULL)
	{
		glfwTerminate();
		error("glfw terminate");
	}
	glfwMakeContextCurrent(rt->gl.window);
	glfwSetWindowUserPointer(rt->gl.window, (void*)rt);
}

static char	*load_shader(char *file)
{
	char	*result;
	int		fd;

	if (!(result = ft_strnew(BUFFER_BYTES)))
		p_error("ft_strnew");
	if ((fd = open(file, O_RDONLY)) < 0)
		p_error("Can't open the shader file");
	if (read(fd, result, BUFFER_BYTES) < 0)
		p_error("Can't read the file");
	close(fd);
	return (result);
}

static void	create_program(t_rt *rt)
{
	rt->gl.vertex_shader_source = "#version 330 core layout (location = 0) \
	in vec3 position; void main() { gl_Position = vec4(position.x, \
	position.y, position.z, 1.0); }";
	rt->gl.fragment_shader_source = load_shader(SHADER_RT_FILE);
	rt->gl.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(rt->gl.fragment_shader, 1,
					(const GLchar **)&(rt->gl.fragment_shader_source), NULL);
	glCompileShader(rt->gl.fragment_shader);
	rt->gl.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(rt->gl.vertex_shader, 1,
					(const GLchar **)&(rt->gl.vertex_shader_source), NULL);
	glCompileShader(rt->gl.vertex_shader);
	rt->gl.shader_program = glCreateProgram();
	glAttachShader(rt->gl.shader_program, rt->gl.vertex_shader);
	glAttachShader(rt->gl.shader_program, rt->gl.fragment_shader);
	glLinkProgram(rt->gl.shader_program);
	ft_strdel(&rt->gl.fragment_shader_source);
	glDeleteShader(rt->gl.vertex_shader);
	glDeleteShader(rt->gl.fragment_shader);
}

static void	put_data_to_gpu(t_rt *rt)
{
	const GLfloat	vertices[] = {1.0f, 1.0f, 0.0f,
								1.0f, -1.0f, 0.0f,
								-1.0f, -1.0f, 0.0f,
								-1.0f, 1.0f, 0.0f};
	const GLuint	indices[] = {0, 1, 3, 1, 2, 3};

	glGenVertexArrays(1, &(rt->gl.vao));
	glGenBuffers(1, &(rt->gl.vbo));
	glGenBuffers(1, &(rt->gl.ebo));
	glBindVertexArray(rt->gl.vao);
	glBindBuffer(GL_ARRAY_BUFFER, rt->gl.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rt->gl.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
				GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
				(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void		gl_init(t_rt *rt)
{
	create_window(rt);
	glfwSetKeyCallback(rt->gl.window,
			(void (*)(struct GLFWwindow *, int, int, int, int))callback_key);
	glfwSetCursorPosCallback(rt->gl.window, callback_cursor_position);
	glfwSetMouseButtonCallback(rt->gl.window, callback_mouse_button);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		error("glewInit is not OK");
	create_program(rt);
	put_data_to_gpu(rt);
}
