#include "mrt.h"

t_vec3	get_reflection_v(t_vec3 surfaceToLight, t_vec3 surfaceNormal)
{
	t_vec3	reflection_v;

	reflection_v = vec_scale(surfaceNormal,
			vec_dot(surfaceNormal, surfaceToLight) * 2);
	return (vec_sub(reflection_v, surfaceToLight));
}

t_vec3	get_surface_normal(t_vec3 point, t_obj *item)
{
	t_vec3	surface_normal;

	if (item->type == OBJ_SPHERE)
	{
		if (item->sphere.camInside)
			surface_normal = vec_sub(item->sphere.center, point);
		else
			surface_normal = vec_sub(point, item->sphere.center);
	}
	else // if (item->t_type == PLANE)
		surface_normal = item->plane.normal;
	surface_normal = vec_norm(surface_normal);
	return (surface_normal);
}

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
	count = item->obj_total;
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
