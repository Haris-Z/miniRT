/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:53:31 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

double	hitSp(t_vec3 origin, t_vec3 ray, t_sphere *sphere)
{

	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	distfar;
	double	distnear;

	a = vec_dot(ray, ray);
	b = -2.0 * vec_dot(ray, vec_sub(origin, sphere->center));
	c = vec_dot(vec_sub(origin, sphere->center), vec_sub(origin, sphere->center)) - sphere->radius * sphere->radius;
	discriminant = (b*b - 4*a*c);
	if (discriminant < 0)
		return (-1.0);
	else
	{
		discriminant = sqrt(discriminant);
		distfar = (b + discriminant ) / (2.0*a);
		distnear = (b - discriminant ) / (2.0*a);
		if (distnear < 0 && distfar > 0)
		{
			sphere->camInside = 1;
			return (distfar);
		}
		return distnear;
	}
}

double	hitPl(t_vec3 origin, t_vec3 ray, t_plane plane)
{
	double	dist;
	double	denom;

	denom = vec_dot(plane.normal, ray);
	if (denom > EPSILON || denom < (-1 * EPSILON))
	{
		dist = vec_dot(vec_sub(plane.point, origin)  , plane.normal) / denom;
		if (dist > 0)
			return dist;
	}
	return (-1.0);
}

void	updateRayDist(t_rt_mlx *vars, t_obj *obj)
{
	int	j;
	double	dist;

	j = -1;
	while(++j < vars->cam.pixels[0])
	{
		if (obj->type == OBJ_SPHERE)
			dist = hitSp(vars->cam.pos, vars->cam.rays[j].direction, &obj->sphere);
		else if (obj->type == OBJ_PLANE)
			dist = hitPl(vars->cam.pos, vars->cam.rays[j].direction, obj->plane);
		if (dist > 0 && (vars->cam.rays[j].dist == -1.0 || dist < vars->cam.rays[j].dist))
		{
			vars->cam.rays[j].dist = dist;
			vars->cam.rays[j].closestitem = obj;
		}
	}
}


int	checkSameSide(t_plane plane, t_vec3 cam, t_vec3 light)
{
	double	planeD;
	double	camD;
	double	lightD;
	
	planeD = vec_dot(plane.normal, plane.point);
	camD = vec_dot(plane.normal, cam);
	lightD = vec_dot(plane.normal, light);
	if (camD > planeD)
	{
		if (lightD > planeD)
			return (1);
		else
			return (0);
	}
	else if (lightD < planeD)
		return (1);
	return (0);
}

t_vec3	getReflectionV(t_vec3 surfaceToLight, t_vec3 surfaceNormal)
{
	t_vec3	reflectionV;

	reflectionV = vec_scale(surfaceNormal, vec_dot(surfaceNormal, surfaceToLight) * 2);
	return (vec_sub(reflectionV, surfaceToLight));
}

t_vec3	getSurfaceNormal(t_vec3 point, t_obj *item)
{
	t_vec3	surfaceNormal;

	if (item->type == OBJ_SPHERE)
	{
		if (item->sphere.camInside)
			surfaceNormal = vec_sub(item->sphere.center, point);
		else
			surfaceNormal = vec_sub(point, item->sphere.center);
	}
	else // if (item->t_type == PLANE)
		surfaceNormal = item->plane.normal;
	surfaceNormal = vec_norm(surfaceNormal);
	return (surfaceNormal);
}

double	distVisible(t_obj **items, t_ray ray, t_vec3 point, t_vec3 surfaceToLight)
{
	t_obj	*item;
	double	res;
	double	dist;

	item = *items;
	res = -1.0;
	while (item)
	{
		if (item == ray.closestitem)
		{
			item = item->next;
			continue;
		}
		if (item->type == OBJ_SPHERE)
			dist = hitSp(point, surfaceToLight, &item->sphere);
		if (item->type == OBJ_PLANE)
			dist = hitPl(point, surfaceToLight, item->plane);
		if (dist > 0 && (dist < res || res < 0))
			res = dist;
		item = item->next;
	}
	return (res);
}

double	getLightAngle(t_vec3 oPoint, t_ray ray, t_vec3 light, t_obj *items)
{
	t_vec3	point;
	t_vec3	surfaceNormal;
	t_vec3	surfaceToLight;
	double	res;
	double	distToVisible;

	point = vec_add(oPoint, vec_scale(ray.direction, ray.dist));
	surfaceToLight = vec_norm(vec_sub(light, point));
	if (ray.closestitem->type == OBJ_PLANE && !checkSameSide(ray.closestitem->plane, oPoint, light))
		return (-1.0);	
	surfaceNormal = getSurfaceNormal(point, ray.closestitem);
	res = vec_dot(surfaceNormal, surfaceToLight);
	if (res < 0)
	{
		if (ray.closestitem->type == OBJ_PLANE)
			res = fabs(res);
		else
			return (-1.0);
	}
	distToVisible = distVisible(&items, ray, point, surfaceToLight);
	if ((distToVisible > 0) && (distToVisible < getDistBetweenPoints(point, light)))
		return (-1.0);
	return (res);
}
