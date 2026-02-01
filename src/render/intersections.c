#include "mrt.h"

static double	get_visible_hit(double a, double b, double c, t_sphere *sphere)
{
	double	discriminant;
	double	distfar;
	double	distnear;

	discriminant = (b * b - 4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	else
	{
		discriminant = sqrt(discriminant);
		distfar = (b + discriminant) / (2.0 * a);
		distnear = (b - discriminant) / (2.0 * a);
		if (distnear < 0 && distfar > 0)
		{
			sphere->camInside = 1;
			return (distfar);
		}
		return (distnear);
	}
}

double	hit_sp(t_vec3 origin, t_vec3 ray, t_sphere *sphere)
{
	double	a;
	double	b;
	double	c;

	a = vec_dot(ray, ray);
	b = -2.0 * vec_dot(ray, vec_sub(origin, sphere->center));
	c = vec_dot(vec_sub(origin, sphere->center), \
		vec_sub(origin, sphere->center))
		- sphere->radius * sphere->radius;
	return (get_visible_hit(a, b, c, sphere));
}

double	hit_pl(t_vec3 origin, t_vec3 ray, t_plane plane)
{
	double	dist;
	double	denom;

	denom = vec_dot(plane.normal, ray);
	if (denom > EPSILON || denom < (-1 * EPSILON))
	{
		dist = vec_dot(vec_sub(plane.point, origin), plane.normal) / denom;
		if (dist > 0)
			return (dist);
	}
	return (-1.0);
}
