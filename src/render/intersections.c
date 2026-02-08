#include "mrt.h"

static double	get_visible_hit(double a, double b, double c, t_sphere *sphere)
{
	double	discriminant;
	double	distfar;
	double	distnear;

	discriminant = (b * b - 4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	else
	{
		discriminant = sqrt(discriminant);
		distfar = (b + discriminant) / (2.0 * a);
		distnear = (b - discriminant) / (2.0 * a);
		if (distnear < 0 && distfar > 0)
		{
			sphere->camInside = 1;
			return (distfar);
		}
		return (distnear);
	}
}

double	hit_sp(t_vec3 origin, t_vec3 ray, t_sphere *sphere)
{
	double	a;
	double	b;
	double	c;

	a = vec_dot(ray, ray);
	b = -2.0 * vec_dot(ray, vec_sub(origin, sphere->center));
	c = vec_dot(vec_sub(origin, sphere->center), \
		vec_sub(origin, sphere->center))
		- sphere->radius * sphere->radius;
	return (get_visible_hit(a, b, c, sphere));
}

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


/*######################################################################*/
/*						CYLINDER INTERSECTIONS							*/
/*######################################################################*/

// // refactor note: -> move to cy_intersection.c/hit_cy.c

/*
** utils
**
** vector projection / rejection
** vec_sub(v, vec_scale(axis, vec_dot(v, axis)))
** remove component of vector v - that points along the cy axis
** v_parallel = axis * dot(v, axis)
** v_perp     = v - v_parallel
** cylinder side defined by distance to its axis line.
** - remving along-axis part of v, leaves the radial/perp part (x,y,0)
**   - now side intersection becomes normal quadratic equation.
**   - problem reduced to 2D circle problem in the plane perpendicular to axis
** axis has to be normalized to behave correctly.
** returns vector that is perpendicular to axis
**
** refactor to (vec_sub(v, vec_scale(axis, vec_dot(v, axis))));
*/
static t_vec3	reject_axis(t_vec3 v, t_vec3 axis)
{
	//t_vec3	axis_normalized;
	double	projection_len;
	t_vec3	projection_vec;
	t_vec3	rejection_vec;

	// normalize axis
	// axis_normalized = vec_normalize(axis);
	// get proj of v onto axis
	projection_len = vec_dot(v, axis);
	// scale axis by p_len -> get p_vec
	// v_paralell
	projection_vec = vec_scale(axis, projection_len);
	// sub proj from v to get rej --> perpendicular compnonent
	// v_perpendicular
	rejection_vec = vec_sub(v, projection_vec);
	return (rejection_vec);
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
static double	min_pos(double a, double b)
{
	if (a > 0.0 && b > 0.0) // both in front of cam, take closer
	{
		if (a < b) 
			return (a);
		return (b);
	}
	if (a > 0.0) // if only a in front
		return (a);
	if (b > 0.0) // if only b in front
		return (b);
	return (NO_HIT); // miss
}

/*
** utils
**
** check if ray origin inside cylinder to flip shade
** then set caminside for side/cap hits.
** point is inside cy if:
**   - axis-coordinate is within [-height/2, +height/2]
**   - its radial distance to axis is < radius
** returns true  if r-dist² < cylinder-radius
** else false
*/
static	bool origin_inside(t_cylinder *cy, t_vec3 origin, double hh)
{
	t_vec3	origin_to_center;
	t_vec3	r;
	double	r_dist_square;

	// v from cy-center to ray-origin - offset from center
	origin_to_center = vec_sub(origin, cy->center);
	// check if origin in within height bounds
	if (fabs(vec_dot(origin_to_center, cy->axis)) > hh + EPSILON)
		return (false);
	// get perpendicualr dist from axis
	// r == o_to_c with axis-part removed
	// r = vec_sub(origin_to_center, vec_scale(cy->axis, vec_dot(origin_to_center, cy->axis)));
	r = reject_axis(origin_to_center, cy->axis); // a 2d vec/coord for exampe (x=2,y=2,z=0)
	r_dist_square = vec_dot(r, r);
	// true if r-distance² - less than radius
	return (r_dist_square < (cy->radius * cy->radius) - EPSILON);
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
** refactor note - use get_visible_dist() ? - would need to remove sp->camInside
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

/*#########################################################################*/
/* ray-cylinder intersection (called in update_ray_dist and dist_visible() */
/*#########################################################################*/

/*
** get all cylinder intersections
**	- side, top/bot-cap and get closest positive hit.
** @return nearest hit distance > 0, else -1.0
*/
double	hit_cy(t_vec3 origin, t_vec3 ray, t_cylinder *cy)
{
	double	t_side;
	double	t_cap_a;
	double	t_cap_b;
	// refactor note:
	//  double	t_hit[3]; t_hit[TOP_CAP], t_hit[SIDE], t_hit[BOT_CAP]
	//  double	t_cap[2];
	t_vec3	cap_a;
	t_vec3	cap_b;
	double	half_height;
	double	t; // closest hit 

	half_height = cy->height * 0.5;
	cy->cam_inside = false;
	// check if ray origin inside/outside
	if (origin_inside(cy, origin, half_height))
		cy->cam_inside = true;
	//cy->cam_inside = origin_inside(cy, origin, half_height);
	// get all possible intersections/hits
	// 	compute center of caps
	// 		bot = center - axis * (height/2)
	cap_a = vec_sub(cy->center, vec_scale(cy->axis, half_height)); // move inside hit_cap
	// 		top = center + axis * (height/2)
	cap_b = vec_add(cy->center, vec_scale(cy->axis, half_height)); // move inside hit_cap
	// solve quadratic for nearest intersection in circle
	t_side = hit_cy_side(origin, ray, cy); // hit distance t to side
	// min_pos(hit_cy_cap, hit_cy_cap);
	t_cap_a = hit_cy_cap(origin, ray, cy, cap_a); // hit dist to bottom cap
	t_cap_b = hit_cy_cap(origin, ray, cy, cap_b); // hit dist to bottom cap
	// t_hit[TOP_CAP],
	// t_hit[SIDE],
	// t_hit[BOT_CAP]
	// directly return min_pos(etc min_pos(etc etc))
	t = min_pos(t_side, min_pos(t_cap_a, t_cap_b));
	return (t);
}
