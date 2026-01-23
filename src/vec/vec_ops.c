/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/23 21:01:06 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

t_vec3	vec_scale(t_vec3 v, double s)
{
	return (vec3(v.x * s, v.y * s, v.z * s));
}

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

double	getDistBetweenPoints(t_vec3 pointA, t_vec3 pointB)
{
	double	res;

	res = pow(pointA.x - pointB.x, 2) +
		pow(pointA.y - pointB.y, 2) +
		pow(pointA.z - pointB.z, 2);
	return (sqrt(res));
}

t_vec3	getSurfaceNormal(t_vec3 point, t_obj *item)
{
	t_vec3	surfaceNormal;

	if (item->type == OBJ_SPHERE)
	{
		if (item->sphere.camInside)
			surfaceNormal = vec_sub(item->sphere.center, point);
		else
			surfaceNormal = vec_sub(point, item->sphere.center);
	}
	else // if (item->t_type == PLANE)
		surfaceNormal = item->plane.normal;
	surfaceNormal = vec_norm(surfaceNormal);
	return (surfaceNormal);
}
