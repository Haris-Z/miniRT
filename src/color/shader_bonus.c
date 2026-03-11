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

t_color	mix_color(t_color ambient, t_color *diffuse, t_color *specular, int num)
{
	t_color	res_l;
	t_color	res;
	int		i;

	i = -1;
	res = color_rgb(0, 0, 0);
	while (++i < num)
	{
		res_l = vec_add(specular[i], diffuse[i]);
		res = vec_add(res, vec_scale(res_l, 0.5));
	}
	res = vec_add(ambient, vec_scale(res, 1.0 / num));
	res.x = rt_clamp(res.x, 0.0, 1.0);
	res.y = rt_clamp(res.y, 0.0, 1.0);
	res.z = rt_clamp(res.z, 0.0, 1.0);
	return (res);
}

t_color	compute_color(t_rt_mlx vars, t_ray ray, t_object *items, int n)
{
	t_color	ambientColor;
	t_color	diffuseColor;
	t_color	specularColor;
	double	lightAngle;
	t_vec3	point;
	t_vec3	surfaceNormal;
	t_vec3	reflectionV;
	double	shining;

	ambientColor = scale_color(color_rgb(0, 0, 0), ray.closestitem->color, vars.cam.ambient.ratio);
	ambientColor = vec_mul(ambientColor, vars.cam.ambient.color);
	lightAngle = get_light_angle(vars.cam.pos, ray, vars.cam.light.pos, items, n);
	if (lightAngle < 0)
	{
		diffuseColor = color_rgb(0, 0, 0);
		shining = 1; 
	}
	else
	{
		diffuseColor = scale_color(color_rgb(0, 0, 0), ray.closestitem->color, lightAngle * vars.cam.light.bright);
		diffuseColor = vec_mul(diffuseColor, vars.cam.light.color);
		point = vec_add(vars.cam.pos, vec_scale(ray.direction, ray.dist));
		surfaceNormal = get_surface_normal(point, ray.direction, ray.closestitem);
		reflectionV = get_reflection_v(vec_norm(vec_sub(vars.cam.light.pos, point)), surfaceNormal);
		shining = vec_dot(reflectionV, ray.direction);
	}
	if (shining > 0)
		specularColor = color_rgb(0, 0, 0);
	else
		specularColor = scale_color(color_rgb(0, 0, 0), vars.cam.light.color, (double)powf(shining, SHINE) * vars.cam.light.bright);
	(void)shining;
	(void)diffuseColor;
	(void)reflectionV;
	(void)specularColor;
	(void)ambientColor;
	// return (specularColor);	
	return (mix_color(ambientColor, &diffuseColor, &specularColor, 1));
	// if (shining < 0)
	// 	return (scale_color(,diffuseColor,2.0 / 3.0));
	// else
	// 	return (scale_color(color_rgb(0,0,0),diffuseColor,2.0 / 3.0));
}
