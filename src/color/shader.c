/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:31:23 by agara             #+#    #+#             */
/*   Updated: 2026/01/23 21:02:35 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	scaleColor(t_color min, t_color max, double amount)
{
	t_vec3	res;

	res.x = ((max.x - min.x) * amount) + min.x;
	res.y = ((max.y - min.y) * amount) + min.y;
	res.z = ((max.z - min.z) * amount) + min.z;
	return (res);
}

// t_vec3	getReflectionV(t_vec3 surfaceToLight, t_vec3 surfaceNormal)
// {
// 	t_vec3	reflectionV;

// 	reflectionV = vec_scale(surfaceNormal, vec_dot(surfaceNormal, surfaceToLight) * 2);
// 	return (vec_sub(reflectionV, surfaceToLight));
// }
int	computeColor(t_cam_rt cam, t_ray ray, t_obj **items)
{
	t_color 	ambientColor;
	t_color		diffuseColor;
	double	lightAngle;
	t_vec3	point;
	t_vec3	surfaceNormal;
	t_vec3	reflectionV;
	double	shining;

	ambientColor = scaleColor(color_rgb(0, 0, 0), ray.closestitem->color, cam.ambient);
	lightAngle = getLightAngle(cam.pos, ray, cam.light, *items);
	if (lightAngle < 0)
		return (ambientColor);
	point = vec_add(cam.pos, vec_scale(ray.direction, ray.dist));
	surfaceNormal = getSurfaceNormal(point, ray.closestitem);
	reflectionV = vec_reflect(vec_norm(vec_sub(cam.light, point)), surfaceNormal);
	diffuseColor = scaleColor(ambientColor, ray.closestitem->color, lightAngle);
	shining = vec_dot(reflectionV, ray.direction);
	if (shining < 0)
		return (color_to_int(scaleColor(diffuseColor, color_rgb(255, 255, 255), pow(shining,32))));
	else
		return (color_to_int(diffuseColor));
}
