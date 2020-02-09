#version 330 core out vec4 color;

// structs
	struct			Flag{
		bool		is_anti_alias;
	};

	struct			Light{
		int			type;
		float		intensity;
		vec3		position;
	};

	struct			Plane{
		vec3		normal;
	};

	struct			Sphere{
		float		radius;
	};

	struct			Cylinder{
		vec3		dir;
		float		radius;
	};

	struct			Cone{
		vec3		dir;
		float		angle;
	};

	struct			Shape{
		int			type;
		bool		marker;
		vec3		position;
		int			specular;
		vec3		color;
		Plane		plane;
		Sphere		sphere;
		Cylinder	cylinder;
		Cone		cone;
	};

	struct			Ray{
		vec3		origin;
		vec3		direction;
		float		t_max;
	};

	struct			Inter{
		Ray			ray;
		float		t;
		Shape		shape;
	};

	struct			Cam{
		float		h;
		float		w;
		vec3		origin;
		vec3		forward;
		vec3		up;
		vec3		right;
	};

//const
	const float		PI = 3.14159265359;

	const float		RAY_T_MIN = 1e-4;
	const float		RAY_T_MAX = 1e30;

	//light types
	const int		AMBIENT = 0;
	const int		POINT = 1;
	const int		LIGHT_TYPES = 2;

	//shape types
	const int		PLANE = 0;
	const int		SPHERE = 1;
	const int		CONE = 2;
	const int		CYLINDER = 3;
	const int		SHAPE_TYPES = 4;

//Uniforms
	//main settings
	uniform vec2	resolution;
	uniform Flag	flag;
	uniform Inter	inter;

	//Obj count
	uniform int		LIGHT_CNT;
	uniform int		SHAPE_CNT;

	//Camera
	uniform Cam		cam;

	//Objects
	uniform Light	lights[32];
	uniform Shape	shapes[64];



// 	void	set_ray_direction(vec2 point)
// 	{
// 		vec3	tmp;

// 		tmp = cam.right * (point.x * cam.w);
// 		inter.ray.direction = cam.up * (point.y * cam.h);
// 		inter.ray.direction = inter.ray.direction + tmp;
// 		inter.ray.direction = inter.ray.direction + cam.forward;
// //		inter.ray.direction = normalize(inter.ray.direction);
// 	}

	void	init_ray(vec2 tmp_xy)
	{
		vec2	screen_coord;

//		inter.t = RAY_T_MAX;
//		screen_coord = vec2((2.0 * tmp_xy.x) / resolution.x - 1.0,
//							(-2.0 * tmp_xy.y) / resolution.y + 1.0);
//		set_ray_direction(inter->ray, &screen_coord, &src->rt->cam);
	}

	vec4	anti_aliasing(vec2 xy, float incrementer)
	{
		vec2	tmp_xy = xy;
		vec4	total_color = vec4(0.0, 0.0, 0.0, 1.0);
		float	total_light = 0.0;
		int		hit = 0;

		while (tmp_xy.x < xy.x + 1)
		{
			tmp_xy.y = xy.y;
			while (tmp_xy.y < xy.y + 1)
			{
				init_ray(tmp_xy);
		// 		if (shapeset_intersect(inter, src->rt->shapes) && ++hit)
		// 		{
		// 			total_light += compute_light(inter, src->rt->shapes, src->rt->lights);
		// 			if (!src->rt->marker || inter->shape->marker == TRUE)
		// 				total_color = color_add(total_color, *(get_color_from_list(inter->shape)));
		// 			else
		// 				total_color = color_add(total_color, (t_color){255, 255, 255});
		// 		}
				tmp_xy.y += incrementer;
			}
			tmp_xy.x += incrementer;
		}
		// make_average(&total_color, &total_light, hit);
		// return get_color(&(total_color), total_light);
		return (vec4(0.0, xy.x / resolution.x, xy.y / resolution.y, 1.0));
	}

	void	main(){
		//inter.shape = Shape(0);
		vec2	point_on_screen;
		float	aliasing_incrementer;

		point_on_screen =
			vec2(gl_FragCoord.x / 2.0, resolution.y - gl_FragCoord.y / 2.0);
		aliasing_incrementer = flag.is_anti_alias ? 0.25 : 1;
		color = anti_aliasing(point_on_screen, aliasing_incrementer);
//		color = vec4(0.0, point_on_screen.x / resolution.x, point_on_screen.y / resolution.y, 1.0);
	}
