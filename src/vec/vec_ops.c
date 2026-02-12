/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:50:52 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_vec3	vec_scale(t_vec3 v, double s)
{
	return (vec3(v.x * s, v.y * s, v.z * s));
}

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
	// return (fma(a.x, b.x, fma(a.y, b.y, a.z * b.z)));
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

double	get_dist_between_p(t_vec3 pointA, t_vec3 pointB)
{
	double	res;

	res = pow(pointA.x - pointB.x, 2)
		+ pow(pointA.y - pointB.y, 2)
		+ pow(pointA.z - pointB.z, 2);
	return (sqrt(res));
}

t_vec3	vec_mul_m(t_vec3 v, t_mat3 m)
{
	t_vec3	res;

	res.x = v.x * m.colx.x + v.y * m.coly.x + v.z * m.colz.x;
	res.y = v.x * m.colx.y + v.y * m.coly.y + v.z * m.colz.y;
	res.z = v.x * m.colx.z + v.y * m.coly.z + v.z * m.colz.z;
	return (res);
}
