/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:27:34 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/11 11:11:53 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

// create a vec
t_vec3	vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

// get len of vec
double	vec_len(t_vec3 v)
{
	return (sqrt(vec_dot(v, v)));
}

int	vec_near_zero(t_vec3 v)
{
	double	e;

	e = 1e-9;
	if (fabs(v.x) < e && fabs(v.y) < e && fabs(v.z) < e)
		return (1);
	return (0);
}

t_vec3	vec_reflect(t_vec3 v, t_vec3 norm)
{
	return (vec_sub(v, vec_scale(norm, 2.0 * vec_dot(v, norm))));
}