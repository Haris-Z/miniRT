/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:47:05 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/18 20:08:39 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

// static double	get_visible_hit(double a, double b, double c)
// {
// 	double	discriminant;
// 	double	dist_far;
// 	double	dist_near;
// 
// 	discriminant = (b * b - 4 * a * c);
// 	if (discriminant < 0.0)
// 		return (NO_HIT);
// 	discriminant = sqrt(discriminant);
// 	dist_far = (b + discriminant) / (2.0 * a);
// 	dist_near = (b - discriminant) / (2.0 * a);
// 	if (dist_near > EPSILON)
// 		return (dist_near);
// 	if (dist_far > EPSILON)
// 		return (dist_far);
// 	return (NO_HIT);
// }

static double	get_visible_hit(double a, double b, double c)
{
	double	roots[2];

	if (!solve_quadratic(a, b, c, roots))
		return (NO_HIT);
	if (roots[0] > EPSILON)
		return (roots[0]);
	if (roots[1] > EPSILON)
		return (roots[1]);
	return (NO_HIT);
}

double	hit_sp(t_vec3 origin, t_vec3 ray, t_sphere *sphere)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;

	oc = vec_sub(origin, sphere->center);
	a = vec_dot(ray, ray);
	b = 2.0 * vec_dot(ray, oc);
	c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	return (get_visible_hit(a, b, c));
}

// double	hit_sp(t_vec3 origin, t_vec3 ray, t_sphere *sphere)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 
// 	a = vec_dot(ray, ray);
// 	// b = -2.0 * vec_dot(ray, vec_sub(origin, sphere->center));
// 	b = 2.0 * vec_dot(ray, vec_sub(origin, sphere->center));
// 	c = vec_dot(vec_sub(origin, sphere->center), \/
// 		vec_sub(origin, sphere->center))
// 		- sphere->radius * sphere->radius;
// 	return (get_visible_hit(a, b, c));
// }

double	hit_pl(t_vec3 origin, t_vec3 ray, t_plane plane)
{
	double	dist;
	double	denom;

	denom = vec_dot(plane.normal, ray);
	if (denom > EPSILON || denom < (-1 * EPSILON))
	{
		dist = vec_dot(vec_sub(plane.point, origin), plane.normal) / denom;
		if (dist > 0)
			return (dist);
	}
	return (-1.0);
}
