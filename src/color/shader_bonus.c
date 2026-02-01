#include "mrt.h"

// ambient : 0			-> itemColor	| userInput
// diffuse : ambient	-> itemColor	| lightAngle
// specular: diffuse	-> 255			| viewAngle

int	scaleColor(int min, int max, double amount)
{
	int	red;
	int	green;
	int	blue;

	red = ((max & 0x00FF0000) - (min & 0x00FF0000)) >> 16;
	red = lround(red * amount) + ((min & 0x00FF0000) >> 16);
	green = ((max & 0x0000FF00) - (min & 0x0000FF00)) >> 8;
	green = lround(green * amount) + ((min & 0x0000FF00) >> 8);
	blue = (max & 0x000000FF) - (min & 0x000000FF);
	blue = lround(blue * amount) + (min & 0x000000FF);

	return((red << 16) | (green << 8) | blue);
}

int	computeColor(t_rt_mlx vars, t_ray ray, t_obj **items)
{
	int 	ambientColor;
	int		diffuseColor;
	double	lightAngle;
	t_vec3	point;
	t_vec3	surfaceNormal;
	t_vec3	reflectionV;
	double	shining;

	ambientColor = scaleColor(0, ray.closestitem->color, vars.cam.ambient);
	lightAngle = getLightAngle(vars.cam.pos, ray, vars.cam.light, *items);
	if (lightAngle < 0)
		return (ambientColor);
	point = vec_add(vars.cam.pos, vec_scale(ray.direction, ray.dist));
	surfaceNormal = getSurfaceNormal(point, ray.closestitem);
	reflectionV = getReflectionV(vec_norm(vec_sub(vars.cam.light, point)), surfaceNormal);
	diffuseColor = scaleColor(ambientColor, ray.closestitem->color, lightAngle);
	shining = vec_dot(reflectionV, ray.direction);
	if (shining < 0)
		return (scaleColor(diffuseColor,0x00FFFFFF, pow(shining,32)));
	else
		return diffuseColor;
}
