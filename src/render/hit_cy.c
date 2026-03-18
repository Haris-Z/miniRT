/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:49:09 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/18 20:46:07 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

static bool		in_height(t_cylinder *cy, t_vec3 p);
static double	hit_cy_side(t_vec3	origin, t_vec3	ray, t_cylinder *cy);
static double	hit_cy_cap(t_vec3 origin, t_vec3 ray,
					t_cylinder *cy, t_vec3 cap_center);
static int		cy_side_coeff(t_vec3 origin, t_vec3 ray,
					t_cylinder *cy, double abc[3]);

double	hit_cy(t_vec3 origin, t_vec3 ray, t_cylinder *cy)
{
	double	t_side;
	double	t_cap_a;
	double	t_cap_b;
	double	t;

	t_side = hit_cy_side(origin, ray, cy);
	t_cap_a = hit_cy_cap(origin, ray, cy, cy_cap_center(cy, BOT_CAP));
	t_cap_b = hit_cy_cap(origin, ray, cy, cy_cap_center(cy, TOP_CAP));
	t = min_pos(t_side, min_pos(t_cap_a, t_cap_b));
	return (t);
}

static double	hit_cy_side(t_vec3	origin, t_vec3	ray, t_cylinder *cy)
{
	double	abc[3];
	double	roots[2];
	t_vec3	p;

	if (!cy_side_coeff(origin, ray, cy, abc))
		return (NO_HIT);
	if (!solve_quadratic(abc[0], abc[1], abc[2], roots))
		return (NO_HIT);
	if (roots[0] > EPSILON)
	{
		p = vec_add(origin, vec_scale(ray, roots[0]));
		if (in_height(cy, p))
			return (roots[0]);
	}
	if (roots[1] > EPSILON)
	{
		p = vec_add(origin, vec_scale(ray, roots[1]));
		if (in_height(cy, p))
			return (roots[1]);
	}
	return (NO_HIT);
}

/*
** intersect ray with one cap disk (plane and disk test).
** called two times in hit_cy() for bottom and top cap.
** returns hit distance > 0, otherwise -1.0.
*/
static double	hit_cy_cap(t_vec3 origin, t_vec3 ray,
				t_cylinder *cy, t_vec3 cap_center)
{
	double	denom;
	double	t;
	t_vec3	p;
	double	d2;
	t_vec3	r;

	denom = vec_dot(ray, cy->axis);
	if (fabs(denom) < EPSILON)
		return (NO_HIT);
	t = vec_dot(vec_sub(cap_center, origin), cy->axis) / denom;
	if (t <= 0.0)
		return (NO_HIT);
	p = vec_add(origin, vec_scale(ray, t));
	r = reject_axis(vec_sub(p, cap_center), cy->axis);
	r = reject_axis(r, cy->axis);
	d2 = vec_dot(r, r);
	if (d2 <= (cy->radius * cy->radius) + EPSILON)
		return (t);
	return (NO_HIT);
}

static bool	in_height(t_cylinder *cy, t_vec3 p)
{
	double	hit;
	double	half_height;
	t_vec3	d;

	half_height = cy->height * 0.5;
	d = vec_sub(p, cy->center);
	hit = vec_dot(d, cy->axis);
	return (hit > -half_height - EPSILON && hit < half_height + EPSILON);
}

static int	cy_side_coeff(t_vec3 origin, t_vec3 ray,
	t_cylinder *cy, double abc[3])
{
	t_vec3	oc;
	t_vec3	d;
	t_vec3	x;

	oc = vec_sub(origin, cy->center);
	d = reject_axis(ray, cy->axis);
	x = reject_axis(oc, cy->axis);
	abc[0] = vec_dot(d, d);
	abc[1] = 2.0 * vec_dot(d, x);
	abc[2] = vec_dot(x, x) - cy->radius * cy->radius;
	if (fabs(abc[0]) < EPSILON)
		return (0);
	return (1);
}

/*
** check if a point p is inside the circular disk area of a cap.
** after ray hits the cap plane, check if the hit is inside the radius.
** returns 1 if inside disk, otherwise 0
*/
// static int	in_cap_disk(t_cylinder *cy, t_vec3 p, t_vec3 cap_center)
// {
// 	t_vec3	v;
// 	t_vec3	r;
// 	double	d2;
// 
// 	v = vec_sub(p, cap_center);
// 	r = reject_axis(v, cy->axis);
// 	d2 = vec_dot(r, r);
// 	return (d2 <= (cy->radius * cy->radius) + EPSILON);
// }