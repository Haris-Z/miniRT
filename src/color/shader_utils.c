#include "mrt.h"

t_vec3	get_reflection_v(t_vec3 surfaceToLight, t_vec3 surfaceNormal)
{
	t_vec3	reflection_v;

	reflection_v = vec_scale(surfaceNormal,
			vec_dot(surfaceNormal, surfaceToLight) * 2);
	return (vec_sub(reflection_v, surfaceToLight));
}


/*######################################################################*/
/*######################################################################*/

/*######################################################################*/
/*######################################################################*/

/*######################################################################*/
/*						CYLINDER CALCULATIONS							*/
/*######################################################################*/
// refactor note: move to extra .c file - norminette
// use cap_center in hit_cy

static t_vec3	reject_axis(t_vec3 v, t_vec3 axis)
{
	return (vec_sub(v, vec_scale(axis, vec_dot(v, axis))));
}

/*
** utils 
** get cap_center of cy top/bot cap
** returns vec that is cap center
*/
static t_vec3	cy_cap_center(t_cylinder *cy, int top)
{
	double	half_height;

	half_height = cy->height * 0.5;
	if (top)
		return (vec_add(cy->center, vec_scale(cy->axis, half_height)));
	return (vec_sub(cy->center, vec_scale(cy->axis, half_height)));
}

/*
** utils
** check if point p lies on the cap plane
** cap is a plane perpendicular to cy->axis, goes trough center of cap
** if p is on plane:
**   dot(p - cap, axis) == 0 + epsilon tolerance
** returns true if p is on the cap plane or close --> else 0.
*/
static int	is_on_cap(t_vec3 p, t_vec3 cap, t_cylinder *cy)
{
	double	d; // distance alonx axis from cap plane
	// vec_sub(p, cap) = v from cap to center p
	// project vec on axis direction
	// if p on plane, than d ~ 0
	d = vec_dot(vec_sub(p, cap), cy->axis);
	return (fabs(d) <= 5.0 * EPSILON);
}

/*
** compute outward normal on the curved side at hit point p.
** side normal == radial direction from the axis line to p.
** returns: unit/norm v outward normal for side surface.
*/
static t_vec3	cy_side_normal(t_vec3 p, t_cylinder *cy)
{
	t_vec3	cp; // v from cy->center to point p
	t_vec3	r;  // (x,y,0)

	cp = vec_sub(p, cy->center); // from center to hit point
	r = reject_axis(cp, cy->axis);
	return (vec_norm(r));
}

/*
** compute correct normal for cylinder parts
** top cap    = normal = +axis
** bottom cap = normal = -axis
** side       = normal = radial direction
*/
static t_vec3	cy_normal(t_vec3 p, t_cylinder *cy)
{
	t_vec3	top;
	t_vec3	bot;
	t_vec3	n;

	bot = cy_cap_center(cy, BOT_CAP);
	top = cy_cap_center(cy, TOP_CAP);
	if (is_on_cap(p, top, cy))
		n = cy->axis;
	else if (is_on_cap(p, bot, cy))
		n = vec_scale(cy->axis, -1.0);
	else
		n = cy_side_normal(p, cy);
	if (cy->cam_inside)						// if inside
		n = vec_scale(n, -1.0);		// flip to face inward
	return (vec_norm(n));
}

t_vec3	get_surface_normal(t_vec3 point, t_obj *item)
{
	t_vec3	surface_normal; // init?

	if (item->type == OBJ_SPHERE)
	{
		if (item->sphere.camInside)
			surface_normal = vec_sub(item->sphere.center, point);
		else
			surface_normal = vec_sub(point, item->sphere.center);
	}
	else if (item->type == OBJ_CYLINDER)
		surface_normal = cy_normal(point, &item->cylinder);
	else // if (item->t_type == OBJ_PLANE)
		surface_normal = item->plane.normal;
	surface_normal = vec_norm(surface_normal);
	return (surface_normal);
}

/* BEFORE CYLINDER */

// t_vec3	get_surface_normal(t_vec3 point, t_obj *item)
// {
// 	t_vec3	surface_normal;

// 	if (item->type == OBJ_SPHERE)
// 	{
// 		if (item->sphere.camInside)
// 			surface_normal = vec_sub(item->sphere.center, point);
// 		else
// 			surface_normal = vec_sub(point, item->sphere.center);
// 	}
// 	else // if (item->t_type == PLANE)
// 		surface_normal = item->plane.normal;
// 	surface_normal = vec_norm(surface_normal);
// 	return (surface_normal);
// }

static int	check_same_side(t_plane plane, t_vec3 cam, t_vec3 light)
{
	double	plane_d;
	double	cam_d;
	double	light_d;

	plane_d = vec_dot(plane.normal, plane.point);
	cam_d = vec_dot(plane.normal, cam);
	light_d = vec_dot(plane.normal, light);
	if (cam_d > plane_d)
	{
		if (light_d > plane_d)
			return (1);
		else
			return (0);
	}
	else if (light_d < plane_d)
		return (1);
	return (0);
}

static double	dist_visible(t_obj **items, t_ray ray,
	t_vec3 point, t_vec3 surfaceToLight)
{
	double	res;
	double	dist;
	int		count;
	int		i;
	t_obj	*item; // array

	if (!items || !*items)
		return (-1.0);
	res = -1.0;
	i = 0;
	item = *items;
	count = (*items)->obj_total;
	// i = -1 , ++i;
	while (i < count)
	{
		if (&item[i] == ray.closestitem)
		{
			i++;
			continue ;
		}
		if (item[i].type == OBJ_SPHERE)
			dist = hit_sp(point, surfaceToLight, &item[i].sphere);
		if (item[i].type == OBJ_PLANE)
			dist = hit_pl(point, surfaceToLight, item[i].plane);
		if (item[i].type == OBJ_CYLINDER)
			dist = hit_cy(point, surfaceToLight, &item[i].cylinder);
		if (dist > 0 && (dist < res || res < 0))
			res = dist;
		i++;
	}
	return (res);
}

/*
**
** PREVIOUS WITH LIST
**
*/
// static double	dist_visible(t_obj **items, t_ray ray,
// 	t_vec3 point, t_vec3 surfaceToLight)
// {
// 	t_obj	*item;
// 	double	res;
// 	double	dist;

// 	item = *items;
// 	res = -1.0;
// 	while (item)
// 	{
// 		if (item == ray.closestitem)
// 		{
// 			item = item->next;
// 			continue ;
// 		}
// 		if (item->type == OBJ_SPHERE)
// 			dist = hit_sp(point, surfaceToLight, &item->sphere);
// 		if (item->type == OBJ_PLANE)
// 			dist = hit_pl(point, surfaceToLight, item->plane);
// 		if (dist > 0 && (dist < res || res < 0))
// 			res = dist;
// 		item = item->next;
// 	}
// 	return (res);
// }

double	get_light_angle(t_vec3 oPoint, t_ray ray, t_vec3 light, t_obj *items)
{
	t_vec3	point;
	t_vec3	surface_normal;
	t_vec3	surface_to_light;
	double	res;
	double	dist_to_visible;

	point = vec_add(oPoint, vec_scale(ray.direction, ray.dist));
	surface_to_light = vec_norm(vec_sub(light, point));
	if (ray.closestitem->type == OBJ_PLANE
		&& !check_same_side(ray.closestitem->plane, oPoint, light))
		return (-1.0);
	surface_normal = get_surface_normal(point, ray.closestitem);
	res = vec_dot(surface_normal, surface_to_light);
	if (res < 0)
	{
		if (ray.closestitem->type == OBJ_PLANE)
			res = fabs(res);
		else
			return (-1.0);
	}
	dist_to_visible = dist_visible(&items, ray, point, surface_to_light);
	if ((dist_to_visible > 0)
		&& (dist_to_visible < getDistBetweenPoints(point, light)))
		return (-1.0);
	return (res);
}
