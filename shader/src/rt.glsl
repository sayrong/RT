#version 330 core out vec4 c;

// structs
	struct			Flag{
		bool		is_anti_alias;
	};

	struct			Ray{
		vec3		origin;
		vec3		direction;
		float		t_max;
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

	//shape types
	const int		PLANE = 0;
	const int		SPHERE = 1;
	const int		CONE = 2;
	const int		CYLINDER = 3;

//Uniforms
	//main settings
	uniform vec2	resolution;
	uniform Flag	flag;

	// //Obj count
	uniform int		LIGHT_CNT;
	uniform int		SHAPE_CNT;

	// //Camera
	uniform Cam		cam;

	// //Lights
	uniform Light	lights[32];

	// //Shapes
	uniform Shape	shapes[64];

	void	main(){
		c = vec4(1.0, 0.0, 0.0, 1.0);
	}
