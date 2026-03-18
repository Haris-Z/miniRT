/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:49:09 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 23:20:01 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

static bool		in_height(t_cylinder *cy, t_vec3 p);
static double	hit_cy_side(t_vec3	origin, t_vec3	ray, t_cylinder *cy);
static double	hit_cy_cap(t_vec3 origin, t_vec3 ray, t_cylinder *cy, t_vec3 cap_center);

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

/*#########################################################################*/
/* cylinder side intersection */
/*#########################################################################*/

/*
** utils
**
** height check for cylindder
** check if a 3D point p is between the caps:
** h = dot(P - center, axis)
** must be between [-height/2, +hight/2].
** a center-based cylinder, caps are at +/- height/2
**
** quadratic gives hits on infinite cy, clamps to finite height
** returns 1 if in range [-height/2, +hight/2]
** if not returns 0.
*/
static bool	in_height(t_cylinder *cy, t_vec3 p)
{
	double	hit;
	double	half_height;
	t_vec3	d;

	half_height = cy->height * 0.5;
	// v from cylinder to center point
	d = vec_sub(p, cy->center);
	// project point onto cylinder axis to get hit distance
	hit = vec_dot(d, cy->axis);
	// check if hit within cylinder bounds
	return (hit > -half_height - EPSILON && hit < half_height + EPSILON);
}

/*
** refactor note - use get_visible_dist()
** compute intersection with curved side of cylinder.
**  - 
** infinite cylinder side intersection using perpendicular components,
** then clamp by finite height.
** return closest valide side hit t that is greater than 0, else -1.0 == no hit
** todo: refactor 
*/
static double	hit_cy_side(t_vec3	origin, t_vec3	ray, t_cylinder *cy)
{
	t_vec3	origin_to_center; // offset
	t_vec3	d; // ray_dir with axis removed (x,y,0)
	t_vec3	x; // origin offsett with axis removed (x,y,0)
	double	a; // coffecient  // double cofficients[4] | coeffiencents[A] etc
	double	b; // coefficient
	double	c; // coefficient
	double	dsc; // discriminant
	double	t1; // close dist t_hit[2] NEAR=0, FAR=1
	double	t2; // far dist
	t_vec3	p; // 3d hitpoint

	origin_to_center = vec_sub(origin, cy->center);
	d = reject_axis(ray, cy->axis); //vec_sub(origin, cy->center);
	// 				vec_sub(origin, cy->center);
	x = reject_axis(origin_to_center, cy->axis);
	//
	a = vec_dot(d, d);
	if (fabs(a) < EPSILON) // no side intersection
		return (NO_HIT);
	b = 2.0 * vec_dot(d, x);
	c = vec_dot(x, x) - (cy->radius * cy->radius);
	dsc = (b * b) - (4.0 * a * c);
	if (dsc < 0.0)
		return (NO_HIT); // miss
	dsc = sqrt(dsc);
	t1 = (-b - dsc) / (2.0 * a); // near
	t2 = (-b + dsc) / (2.0 * a); // far
	// check first intersect p - near -> return
	// t = min_pos(t1, t2);
	// p = vec_add()
	// if in_height(cy, p)
	// 	return (t);
	// return (NO_HIT);
	if (t1 > 0.0)
	{
		p = vec_add(origin, vec_scale(ray, t1));
		if (in_height(cy, p))
			return (t1);
	}
	// check second intersect p - far -> return
	if (t2 > 0.0)
	{
		p = vec_add(origin, vec_scale(ray, t2));
		if (in_height(cy, p))
			return (t2);
	}
	// if intersection above or below [-H/2,+H/2]
	// hit above or below caps
	return (NO_HIT);
}


/*#########################################################################*/
/* cylinder cap intersection */
/*#########################################################################*/

/*
** check if a point p is inside the circular disk area of a cap.
** after ray hits the cap plane, check if the hit is inside the radius.
** returns 1 if inside disk, otherwise 0
*/
static int	in_cap_disk(t_cylinder *cy, t_vec3 p, t_vec3 cap_center)
{
	t_vec3	v;
	t_vec3	r;
	double	d2;

	// v from cap_center to intersect point // offset from cap_center to ppint
	v = vec_sub(p, cap_center);
	// v with axis removed (x,y,0)
	r = reject_axis(v, cy->axis);
	d2 = vec_dot(r, r);
	// check if within cap radius |r| <= radius
	return (d2 <= (cy->radius * cy->radius) + EPSILON);
}

/*
** intersect ray with one cap disk (plane and disk test).
** called two times in hit_cy() for bottom and top cap.
** returns hit distance > 0, otherwise -1.0.
*/
// refactor note: calculate cap_a, cap_b inside hit_cy()
static double hit_cy_cap(t_vec3 origin, t_vec3 ray, t_cylinder *cy, t_vec3 cap_center)
{
	double	denom;
	double	t;
	t_vec3	p;

	// denominatro for plane intersectin
	denom = vec_dot(ray, cy->axis);
	// t = 
	if (fabs(denom) < EPSILON) // || t <= 0.0
		return (NO_HIT);
	// compute intersection dist with cap plane
	t = vec_dot(vec_sub(cap_center, origin), cy->axis) / denom;
	if (t <= 0.0) // behind cam
		return (NO_HIT);
	p = vec_add(origin, vec_scale(ray, t));
	// check if intersection within cap disk
	if (!in_cap_disk(cy, p, cap_center))
		return (NO_HIT); // miss
	return (t);
}
