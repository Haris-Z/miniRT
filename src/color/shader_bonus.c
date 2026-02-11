#include "mrt.h"

// ambient : 0			-> itemColor	| userInput
// diffuse : ambient	-> itemColor	| lightAngle
// specular: diffuse	-> 255			| viewAngle

t_color	scale_color(t_color min, t_color max, double amount)
{
	t_color	res;

	res.x = ((max.x - min.x) * amount) + min.x;
	res.y = ((max.y - min.y) * amount) + min.y;
	res.z = ((max.z - min.z) * amount) + min.z;

	return(res);
}

t_color	compute_color(t_rt_mlx vars, t_ray ray, t_obj **items)
{
	t_color	ambientColor;
	t_color	diffuseColor;
	double	lightAngle;
	t_vec3	point;
	t_vec3	surfaceNormal;
	t_vec3	reflectionV;
	double	shining;

	ambientColor = scale_color(color_rgb(0, 0, 0), ray.closestitem->color, vars.cam.ambient);
	lightAngle = get_light_angle(vars.cam.pos, ray, vars.cam.light.pos, *items);
	if (lightAngle < 0)
		return (ambientColor);
	point = vec_add(vars.cam.pos, vec_scale(ray.direction, ray.dist));
	surfaceNormal = get_surface_normal(point, ray.closestitem);
	reflectionV = get_reflection_v(vec_norm(vec_sub(vars.cam.light.pos, point)), surfaceNormal);
	diffuseColor = scale_color(ambientColor, ray.closestitem->color, lightAngle * vars.cam.light.bright);
	shining = vec_dot(reflectionV, ray.direction);
	if (shining < 0)
		return (scale_color(diffuseColor, color_rgb(255, 255, 255), pow(shining,8) * vars.cam.light.bright));
	else
		return diffuseColor;
}
