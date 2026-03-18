/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:12:15 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/10 15:43:30 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

// always face against incoming ray
t_vec3	set_face_normal(t_vec3 ray_dir, t_vec3 outward) // normal from object
{
	if (vec_dot(ray_dir, outward) > 0.0)
		return (vec_scale(outward, -1.0));
	return (outward);
}

/*
** utils
** note: refactor
** 
** return the smallest positive value between a and b
** used to pick the closest visible hit afer getting all
** possible intersections in hit_cy()  --> (side vs caps).
** return smallest value > 0;
** if neither a or b is > 0, returns -1 (== no hit).
*/
double	min_pos(double a, double b)
{
	if (a > 0.0 && b > 0.0)
	{
		if (a < b)
			return (a);
		return (b);
	}
	if (a > 0.0)
		return (a);
	if (b > 0.0)
		return (b);
	return (NO_HIT);
}
