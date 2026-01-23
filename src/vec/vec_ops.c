/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/22 14:59:47 by agara            ###   ########.fr       */
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
