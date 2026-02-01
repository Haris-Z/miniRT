#include "mrt.h"

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

static int	checkSameSide(t_plane plane, t_vec3 cam, t_vec3 light)
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

static double	distVisible(t_obj **items, t_ray ray, t_vec3 point, t_vec3 surfaceToLight)
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
