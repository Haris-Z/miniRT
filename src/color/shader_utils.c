/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 20:59:32 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 17:34:25 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_vec3	get_reflection_v(t_vec3 surfaceToLight, t_vec3 surfaceNormal)
{
	t_vec3	reflection_v;

	reflection_v = vec_scale(surfaceNormal,
			vec_dot(surfaceNormal, surfaceToLight) * 2);
	return (vec_sub(reflection_v, surfaceToLight));
}

t_vec3	get_surface_normal(t_vec3 point, t_vec3 ray_dir, t_object *item)
{
	t_vec3	surface_normal;

	surface_normal = (t_vec3){0};
	if (item->type == SPHERE)
		surface_normal = vec_norm(vec_sub(point, item->shape.sp.center));
	else if (item->type == CYLINDER)
		surface_normal = cy_normal(point, &item->shape.cy);
	else if (item->type == PLANE)
		surface_normal = vec_norm(item->shape.pl.normal);
	surface_normal = set_face_normal(ray_dir, surface_normal);
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

static double	dist_visible(t_object *items, int n, t_ray ray,
	t_vec3 point, t_vec3 surfaceToLight)
{
	double	res;
	double	dist;
	int		i;

	res = -1.0;
	i = -1;
	while (++i < n)
	{
		if (&items[i] == ray.closestitem)
			continue ;
		dist = NO_HIT;
		if (items[i].type == SPHERE)
			dist = hit_sp(point, surfaceToLight, &items[i].shape.sp);
		else if (items[i].type == PLANE)
			dist = hit_pl(point, surfaceToLight, items[i].shape.pl);
		else if (items[i].type == CYLINDER)
			dist = hit_cy(point, surfaceToLight, &items[i].shape.cy);
		if (dist > EPSILON && (dist < res || res < 0))
			res = dist;
	}
	return (res);
}


double	get_light_angle(t_vec3 oPoint, t_ray ray, t_vec3 light, t_object *items, int n)
{
	t_vec3	point;
	t_vec3	surface_normal;
	t_vec3	surface_to_light;
	double	res;
	double	dist_to_visible;

	point = vec_add(oPoint, vec_scale(ray.direction, ray.dist));
	surface_to_light = vec_norm(vec_sub(light, point));
	if (ray.closestitem->type == PLANE
		&& !check_same_side(ray.closestitem->shape.pl, oPoint, light))
		return (-1.0);
	surface_normal = get_surface_normal(point, ray.direction, ray.closestitem);
	res = vec_dot(surface_normal, surface_to_light);
	if (res < 0.0)
	{
		if (ray.closestitem->type == PLANE)
			res = fabs(res);
		else
			return (-1.0);
	}
	dist_to_visible = dist_visible(items, n, ray, point, surface_to_light);
	if ((dist_to_visible > 0.0)
		&& ((get_dist_between_p(point, light) - dist_to_visible) > EPSILON))
		return (-1.0);
	return (res);
}
