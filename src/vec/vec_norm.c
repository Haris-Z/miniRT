/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:07:32 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 12:34:08 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

int	vec_near_zero(t_vec3 v)
{
	double	e;

	e = 1e-9;
	if (fabs(v.x) < e && fabs(v.y) < e && fabs(v.z) < e)
		return (1);
	return (0);
}

t_vec3	vec_norm(t_vec3 v)
{
	double	len;

	len = vec_len(v);
	if (len < 1e-12)
		return (vec3(0.0, 0.0, 0.0));
	return (vec_scale(v, 1.0 / len));
}

t_vec3	vec_reflect(t_vec3 v, t_vec3 norm)
{
	return (vec_sub(v, vec_scale(norm, 2.0 * vec_dot(v, norm))));
}