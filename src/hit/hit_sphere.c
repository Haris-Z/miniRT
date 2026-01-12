/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:00:55 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:09:02 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "mini.h"
#include "scene.h"
#include "hit.h"
#include <math.h>

static int	find_closest_root(double a, double half_b, double disc,
							double tmin, double tmax, t_hit *hit)
{
	double	sqrt_disc;
	double	root;
	
	sqrt_disc = sqrt(disc);
	root = (-half_b - sqrt_disc) / a;
	if (root < tmin || root > tmax)
	{
		root = (-half_b + sqrt_disc) / a;
		if (root < tmin || root > tmax)
			return (0);
	}
	hit->t = root;
	return (1);
}

int	hit_sphere(t_sphere *sp, t_ray ray,
						double tmin, double tmax, t_hit *hit)
{
	t_vec3	offset_c;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	offset_c = vec_sub(ray.origin, sp->center);
	a = vec_dot(ray.direction, ray.direction);
	half_b = vec_dot(offset_c, ray.direction);
	c = vec_dot(offset_c, offset_c) - (sp->radius * sp->radius);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0)
		return (0);
	return (find_closest_root(a, half_b, discriminant, tmin, tmax, hit));
}

// double	hit_sphere(vector ray, t_item ball)
// {

// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;

// 	a = dotv(ray, ray);
// 	b = -2.0 * dotv(ray, ball.pos);
// 	c = dotv(ball.pos, ball.pos) - ball.radius * ball.radius;
// 	discriminant = (b*b - 4*a*c);
// 	// printf("discriminant: %f\n", discriminant);
// 	if (discriminant < 0)
// 		return -1.0;
// 	else {
// 		return (-b - sqrt(discriminant) ) / (2.0*a);
// 	}
// }