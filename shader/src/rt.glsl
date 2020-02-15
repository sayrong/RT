#version 330 core out vec4 c;

// structs
	struct Material{
		vec3 color;
		float specular;
		float reflection;
	};

	struct Transform{
		vec3 position;
		vec3 rotation;
	};

	struct Light{
		int type;
		Transform transform;
		//point light: direction.x is radius
		vec3 direction;
		float intensity;
	};

	struct Ray{
		vec3 origin;
		vec3 direction;
	};

	struct Intersection{
		Ray ray;
		float t;
		vec3 normal;
		Material material;
		bool isOutline;
		bool isToon;
	};

	struct Camera{
		Transform transform;
		vec3 direction;
	};

	struct Sphere{
		Transform transform;
		float radius;
		Material material;
		bool isOutline;
		bool isToon;
	};

	struct Plane{
		Transform transform;
		vec3 normal;
		Material material;
	};

	struct Cone{
		Transform transform;
		vec3 axis;
		//Rad
		float angle;
		Material material;
	};

	struct Cylinder{
		Transform transform;
		vec3 axis;
		//Rad
		float radius;
		Material material;
	};

//const
	const float PI  = 3.14159265359;
	const float EPS = 0.00001;
	const int TONE = 0;


	const int LIGHT_DIRECTION = 0;
	const int LIGHT_AMBIENT = 1;
	const int LIGHT_POINT = 2;

	const float OUTLINE_THRESHOLD = 0.0;
	const vec3 OUTLINE_COLOR = vec3(0.9765625, 0.92578125, 0.1484375);


	const float TOON_THRESHOLD = 0.2;
	const float TOON_SHADOW = 0.4;
	const float TOON_LIGHT = 0.7;


	const float SHINE_INTENSITY = 0.007;

	const int RECURSIVE_DEPTH = 3;

	const int SAMPLES = 1;

	// miss intersection
	// (1.0 / 0.0) = MAX_FLOAT
	const Intersection INFINITY = Intersection(Ray(vec3(0.0), vec3(0.0)), 1.0 / 0.0, vec3(0.0), Material(vec3(0.0), 0.0, 0.0), false, false);

//Uniforms
	//main settings
	uniform vec2 resolution;
	uniform float posY;
	uniform int render_type;

	//Camera
	uniform Camera camera;

	//Lights
	uniform Light lights[16];

	//Object count
	uniform int LIGHT_COUNT;
	uniform int CONE_COUNT;
	uniform int CYLINDER_COUNT;
	uniform int SPHERE_COUNT;
	uniform int PLANE_COUNT;

	//Objects
	uniform Plane planes[16];
	uniform Cone cones[16];
	uniform Cylinder cylinders[16];
	uniform Sphere spheres[16];

	vec3 planes_normal[16];
	vec3 cones_axis[16];
	vec3 cylinders_axis[16];

	Intersection applyRay(Intersection intersection, Ray ray)
	{
		return Intersection(ray, intersection.t, intersection.normal,intersection.material, false, false);
	}

	Intersection checkCylinderIntersection(Ray ray, Cylinder cylinder)
	{
		vec3 oc = ray.origin - cylinder.transform.position;
		vec3 h1 = ray.direction - cylinder.axis * dot(ray.direction, cylinder.axis);
		vec3 h2 = oc - cylinder.axis * dot(oc, cylinder.axis);
		float a = dot(h1, h1);
		float b = 2.0 * dot(h1, h2);
		float c = dot(h2, h2) - cylinder.radius * cylinder.radius;
		float dis = b * b - 4.0 * a * c;

		if (dis >= 0.0)
			{
				float t = -1.0;
				float t1 = (-b + sqrt(dis)) / (2.0 * a);
				float t2 = (-b - sqrt(dis)) / (2.0 * a);
				if (t1 > 0.0)
					t = t1;
				if (t2 < t1 && t2 > 0.0)
					t = t2;
				if (t > 0.0)
					{
						vec3 intersect = ray.origin + ray.direction * t;
						vec3 ic = intersect - cylinder.transform.position;
						vec3 at = cylinder.transform.position + cylinder.axis * dot(ic, cylinder.axis);
						return Intersection(ray, t, normalize(intersect - at), cylinder.material, false, false);
					}
			}
		return applyRay(INFINITY, ray);
	}

	Intersection checkConeIntersection(Ray ray, Cone cone){
		float cosa = cos(cone.angle);
		vec3 co = ray.origin - cone.transform.position;
		float a = dot(ray.direction, cone.axis) * dot(ray.direction, cone.axis) - cosa * cosa;
		float b = 2. * (dot(ray.direction, cone.axis) * dot(co, cone.axis) - dot(ray.direction, co)* cosa * cosa);
		float c = dot(co, cone.axis) * dot(co, cone.axis) - dot(co, co) * cosa * cosa;

		float dis = b * b - 4.0 * a * c;

		if (dis >= 0.0)
			{
				float t = -1.0;
				float t1 = (-b + sqrt(dis)) / (2.0 * a);
				float t2 = (-b - sqrt(dis)) / (2.0 * a);
				if (t1 > 0.0)
					t = t1;
				if (t2 < t1 && t2 > 0.0)
					t = t2;
				if (t > 0.0)
					{
						vec3 cp = ray.origin + t * ray.direction - cone.transform.position;
						float dotAxisSide = dot(cone.axis, cp);
						vec3 normal = (cp * dot(cone.axis, cp) / dot(cp, cp) - cone.axis) * (dotAxisSide / abs(dotAxisSide));
						return Intersection(ray, t, normalize(normal), cone.material, false, false);
					}
			}
		return applyRay(INFINITY, ray);
	}

	Intersection checkPlaneIntersection(Ray ray, Plane plane){
		float dotRN =  dot(ray.direction, -plane.normal);
		if (dotRN > 0.0)
			{
				float t = dot(plane.transform.position - ray.origin, -plane.normal) / dotRN;
				if (t >= 0.001)
					return Intersection(ray, t, plane.normal, plane.material, false, false);
			}
		return applyRay(INFINITY, ray);
	}

	Intersection checkSphereIntersection(Ray ray, Sphere sphere)
	{
		vec3 oc = ray.origin - sphere.transform.position;
		float t = -1.;
		float k1 = dot(ray.direction, ray.direction);
		float k2 = 2.0 * dot(ray.direction, oc);
		float k3 = dot(oc, oc) - sphere.radius * sphere.radius;
		float dis = k2 * k2 - 4.0 * k1 * k3;
		if (dis >= 0.0)
			{
				float t1 = (-k2 + sqrt(dis)) / (2.0 * k1);
				float t2 = (-k2 - sqrt(dis)) / (2.0 * k1);
				if (t1 > 0.0)
					t = t1;
				if (t2 < t1 && t2 > 0.0)
					t = t2;
				if (t > 0.0)
					return Intersection(ray, t, normalize(ray.origin + ray.direction * t - sphere.transform.position), sphere.material, (dis < OUTLINE_THRESHOLD && sphere.isOutline), sphere.isToon);
			}
		return applyRay(INFINITY, ray);
	}

	// return color
	vec3 Uncharted2ToneMapping(vec3 color)
	{
		float A = 0.15;
		float B = 0.50;
		float C = 0.10;
		float D = 0.20;
		float E = 0.02;
		float F = 0.30;
		float W = 11.2;
		float exposure = 0.012;
		float gamma = 2.2;
		color *= exposure;
		color = ((color * (A * color + C * B) + D * E) / (color * (A * color + B) + D * F)) - E / F;
		float white = ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F;
		color /= white;
		color = pow(color, vec3(1.0 / gamma));
		return color;
	}

	vec3 mirroredRay(vec3 ray, Intersection intersection)
	{
		return normalize(2.0 * intersection.normal * dot(intersection.normal, -ray) + ray);
	}

	Intersection castRay(Ray ray, float t_min, float t_max){
		Intersection intersection = INFINITY;
		Intersection currentIntersection;
		for(int i = 0; i < SPHERE_COUNT; i++){
			currentIntersection = checkSphereIntersection(ray, spheres[i]);
			if (currentIntersection.t < intersection.t && currentIntersection.t < t_max && currentIntersection.t > t_min)
				intersection = currentIntersection;
		}
		for(int i = 0; i < PLANE_COUNT; i++){
			currentIntersection = checkPlaneIntersection(ray, Plane(planes[i].transform, planes_normal[i], planes[i].material));
			if (currentIntersection.t < intersection.t && currentIntersection.t < t_max && currentIntersection.t > t_min)
				intersection = currentIntersection;
		}
		for(int i = 0; i < CONE_COUNT; i++){
			currentIntersection = checkConeIntersection(ray, Cone(cones[i].transform, cones_axis[i], cones[i].angle, cones[i].material));
			if (currentIntersection.t < intersection.t && currentIntersection.t < t_max && currentIntersection.t > t_min)
				intersection = currentIntersection;
		}
		for(int i = 0; i < CYLINDER_COUNT; i++){
			currentIntersection = checkCylinderIntersection(ray, Cylinder(cylinders[i].transform, cylinders_axis[i], cylinders[i].radius, cylinders[i].material));
			if (currentIntersection.t < intersection.t && currentIntersection.t < t_max && currentIntersection.t > t_min)
				intersection = currentIntersection;
		}
		if(intersection.t == INFINITY.t)
			intersection = applyRay(intersection, ray);
		return intersection;
	}

	float phongShading(Intersection intersection)
	{
		float dotRayNormal = dot(-intersection.ray.direction, intersection.normal);

		return clamp(dotRayNormal, 0.2, 1.0) * 0.6;
	}

	vec2 computeLight(Intersection intersection, Ray ray)
	{
		float intenDepRadius = 1.0;
		float lightIntensity = 0.0;
		float specularIntensity = 0.0;
		vec3 lightDirection;
		for(int i = 0; i < LIGHT_COUNT; i++)
		{
			if(lights[i].type == LIGHT_AMBIENT)
				lightIntensity += lights[i].intensity;
			else
				{
					float t_max;

					if (lights[i].type == LIGHT_POINT)
						{
							vec3 r = lights[i].transform.position - (ray.origin + ray.direction * intersection.t);
							t_max = length(r);
							intenDepRadius = 1.0 - clamp(t_max / lights[i].direction.x , 0.0, 1.0);
							lightDirection = normalize(r);
						}
					else
						{
							t_max = INFINITY.t;
							lightDirection = -lights[i].direction;
						}

					Intersection shadow = castRay(Ray((ray.origin + ray.direction * intersection.t + intersection.normal * EPS * intersection.t), lightDirection), EPS, t_max);
					if(shadow.t < INFINITY.t)
						continue;

					//diffuse
					float dotNormalLiDe = dot(intersection.normal, lightDirection);
					if (dotNormalLiDe > 0.0)
						lightIntensity += lights[i].intensity * dotNormalLiDe / length(lightDirection) / length(intersection.normal) * intenDepRadius;

					//specular
					if (intersection.material.specular > 0.0)
						{
							vec3 mR = mirroredRay(-lightDirection, intersection);
							float dotmRView = dot(mR, -ray.direction);
							if (dotmRView > 0.0)
								specularIntensity += lights[i].intensity * pow(dotmRView / length(mR) / length(ray.direction), intersection.material.specular) * intenDepRadius;
						}

				}
		}
		return vec2(lightIntensity, specularIntensity);
	}


	vec3 start(Ray ray)
	{
		Intersection chainIntersection[RECURSIVE_DEPTH + 1];
		chainIntersection[0] = castRay(ray, 0.0, INFINITY.t);
		if (chainIntersection[0].t == INFINITY.t)
			return vec3(0.0);
		if (render_type == 1)
		{
			int mirrorCount = 0;
			for (int i = 1; i < RECURSIVE_DEPTH + 1; i++)
			{
				if(chainIntersection[i - 1].material.reflection > 0.0 && chainIntersection[i - 1].t != INFINITY.t)
				{
					vec3 mR = mirroredRay(chainIntersection[i - 1].ray.direction, chainIntersection[i - 1]);
					chainIntersection[i] = castRay(Ray((ray.origin + ray.direction * chainIntersection[i - 1].t + chainIntersection[i - 1].normal * EPS * chainIntersection[i - 1].t), mR), 0.0, INFINITY.t);
					mirrorCount++;
				}
				else
					break;
			}

			for (int i = RECURSIVE_DEPTH; i > 0; i--)
			{
				if (i <= mirrorCount)
				{
					vec3 reflection_color = chainIntersection[i].material.color;
					if (chainIntersection[i].t == INFINITY.t)
						reflection_color = INFINITY.material.color;
					chainIntersection[i - 1].material.color = chainIntersection[i - 1].material.color * (1.0 - chainIntersection[i - 1].material.reflection) + reflection_color * chainIntersection[i - 1].material.reflection;
				}
			}
			Intersection intersection = chainIntersection[0];
			//if (intersection.isOutline)
			//	return OUTLINE_COLOR;
			//light
			vec2 lightAndSpecularIntensity = computeLight(intersection, ray);
			//it's magic

			return lightAndSpecularIntensity.x * intersection.material.color + vec3(1.0) * lightAndSpecularIntensity.y * intersection.material.specular / 500;
		}
		return chainIntersection[0].material.color * phongShading(chainIntersection[0]);
	}

	//rotation
	vec3 rotationX(vec3 vector, float angle)
	{
		angle = -angle;
		mat3 rotationMatrix = mat3(vec3(1.0, 0.0, 0.0), vec3(0.0, cos(angle), sin(angle)), vec3(0.0, -sin(angle), cos(angle)));
		return rotationMatrix * vector;
	}

	vec3 rotationY(vec3 vector, float angle)
	{
		angle = -angle;
		mat3 rotationMatrix = mat3(vec3(cos(angle), 0.0, -sin(angle)), vec3(0.0, 1.0, 0.0), vec3(sin(angle), 0.0, cos(angle)));
		return rotationMatrix * vector;
	}

	vec3 rotationZ(vec3 vector, float angle)
	{
		angle = -angle;
		mat3 rotationMatrix = mat3(vec3(cos(angle), sin(angle), 0.0), vec3(-sin(angle), cos(angle), 0.0), vec3(0.0, 0.0, 1.0));
		return rotationMatrix * vector;
	}

	void applyRotation()
	{
		for(int i = 0; i < PLANE_COUNT; i++){
			planes_normal[i] = rotationZ(rotationY(rotationX(vec3(0.0, 0.0, 1.0), planes[i].transform.rotation.x / 180.0 * PI), planes[i].transform.rotation.y / 180.0 * PI), planes[i].transform.rotation.z / 180.0 * PI);
		}
		for(int i = 0; i < CONE_COUNT; i++){
			cones_axis[i] = rotationZ(rotationY(rotationX(vec3(0.0, 0.0, 1.0), cones[i].transform.rotation.x / 180.0 * PI), cones[i].transform.rotation.y / 180.0 * PI), cones[i].transform.rotation.z / 180.0 * PI);
		}
		for(int i = 0; i < CYLINDER_COUNT; i++){
			cylinders_axis[i] = rotationZ(rotationY(rotationX(vec3(0.0, 0.0, 1.0), cylinders[i].transform.rotation.x / 180.0 * PI), cylinders[i].transform.rotation.y / 180.0 * PI), cylinders[i].transform.rotation.z / 180.0 * PI);
		}
	}

	void main(){
		//init lights
		//lights[0] = Light(LIGHT_DIRECTION, Transform(vec3(0.0), vec3(0.0)), normalize(vec3(0.5, -0.5, 1.0)), 0.3);
		//lights[1] = Light(LIGHT_AMBIENT, Transform(vec3(0.0), vec3(0.0)), vec3(0.0), 0.2);
		//lights[2] = Light(LIGHT_DIRECTION, Transform(vec3(0.0), vec3(0.0)), normalize(vec3(-0.5, -0.5, 1.0)), 0.4);
		// Чисто ради теста
		//float angle = (1.0 + sin(posY)) * PI * 4.0;
		//lights[2] = Light(LIGHT_POINT, Transform(vec3( 2.0, 3.0 + posY * 10.0, -10.0), vec3(0.0)), vec3(200.0), 0.5);

		//init spheres
		//spheres[0] = Sphere( Transform(vec3(0.0, -1.0, 3.0), vec3(0.0)), 1.0, Material(vec3(1., 0., 0.), 100.0, 0.1), false, false);
		//spheres[1] = Sphere( Transform(vec3(2.0, 0.0, 4.0), vec3(0.0)), 1.0, Material(vec3(0.5), 1000.0, 0.8), false, false);
		//spheres[2] = Sphere( Transform(vec3(-2.0, 0.0, 4.0), vec3(0.0)), 1.0, Material(vec3(0., 0., 1.), 10.0, 0.1), false, false);
		//spheres[3] = Sphere( Transform(vec3(7.0, -5001.0, 4.0), vec3(0.0)), 5000.0, Material(vec3(0.5, 0.5, 0.5), 1.), false, false);

		//init planes
		//planes[0] = Plane( Transform(vec3(-2.0), vec3(0.0)), vec3(0.0, 1.0, 0.0), Material(vec3(1.0), 0.0, 0.1));
		//planes[1] = Plane(vec3(10.0), vec3(0.0, 0.0, -1.0), Material(vec3(1.0, 1.0, 0.0), 1.0));

		// init cones
		//cones[0] = Cone(Transform(vec3(0.0, 9.0, 14.0), vec3(0.0)), vec3(1.0, 0.0, 0.0), PI / 10.0, Material(vec3(1., 0., 1.), 0.0, 0.1));

		//cylinders[0] = Cylinder(Transform(vec3(0.0, 0.0, 15.0), vec3(0.0)), normalize(vec3(0.0, 1.0, 0.0)), 2.0, Material(vec3(1., 0., 0.), 0.0, 0.1));

		applyRotation();
		vec2 ratio = vec2(resolution.x / resolution.y / 2.0, 0.5);
		vec2 pos = gl_FragCoord.xy / resolution.xy;

		// сглаживание
		vec2 rays[4];
		float step = 1. / resolution.x / 4.;
		rays[0] = vec2(step, step);
		rays[1] = vec2(step, -step);
		rays[2] = vec2(-step, step);
		rays[3] = vec2(-step, -step);
		vec3 color = vec3(0.0);
		for (int i = 0; i < SAMPLES; i++){
			vec3 pointOnPlane = normalize(vec3(pos * ratio - ratio , 1.0));
			vec3 rotatedPoint = rotationY(rotationX(pointOnPlane, -camera.transform.rotation.y / 180.0 * PI), -camera.transform.rotation.x / 180.0 * PI);
			Ray ray = Ray(camera.transform.position, rotatedPoint);
			color += start(ray);
		}
		// тоже ради тестов
		if (TONE == 1)
			c = vec4(Uncharted2ToneMapping(color / float(SAMPLES)), 1.0);
		else
			c = vec4(color / float(SAMPLES), 1.0);
	}
