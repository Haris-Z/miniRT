#include "../includes/mini.h"
double	hitSp(vector origin, vector ray, t_sphere sphere)
{

	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	distfar;
	double	distnear;

	a = dotv(ray, ray);
	b = -2.0 * dotv(ray, subv(origin, sphere.pos));
	c = dotv(subv(origin, sphere.pos), subv(origin, sphere.pos)) - sphere.radius * sphere.radius;
	discriminant = (b*b - 4*a*c);
	if (discriminant < 0)
		return (-1.0);
	else
	{
		discriminant = sqrt(discriminant);
		distfar = (b + discriminant ) / (2.0*a);
		distnear = (b - discriminant ) / (2.0*a);
		if (distnear < 0 && distfar > 0)
			return (distfar);
		return distnear;
	}
}
// ambient : 0			-> itemColor	| userInput
// diffuse : ambient	-> itemColor	| lightAngle
// specular: diffuse	-> 255			| viewAngle

int	scaleColor(int min, int max, double amount)
{
	int	red;
	int	green;
	int	blue;

	red = ((max & 0x00FF0000) - (min & 0x00FF0000)) >> 16;
	red = lround(red * amount) + ((min & 0x00FF0000) >> 16) << 16;
	green = (max & 0x0000FF00) - (min & 0x0000FF00) >> 8 ;
	green = lround(green * amount) + ((min & 0x0000FF00) >> 8) << 8;
	blue = (max & 0x000000FF) - (min & 0x000000FF);
	blue = lround(blue * amount) + (min & 0x000000FF);

	return(red + green + blue);
}

double	getDistBetweenPoints(vector pointA, vector pointB)
{
	double	res;

	res = pow(pointA.x - pointB.x, 2) +
		pow(pointA.y - pointB.y, 2) +
		pow(pointA.z - pointB.z, 2);
	return (sqrt(res));
}

int	checkSameSide(t_plane plane, vector cam, vector light)
{
	double	planeD;
	double	camD;
	double	lightD;
	
	planeD = plane.orientation.x * plane.point.x + plane.orientation.y * plane.point.y +plane.orientation.z * plane.point.z;
	camD = plane.orientation.x * cam.x + plane.orientation.y * cam.y +plane.orientation.z * cam.z;
	lightD = plane.orientation.x * light.x + plane.orientation.y * light.y +plane.orientation.z * light.z;
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

vector	getReflectionV(vector surfaceToLight, vector surfaceNormal)
{
	vector	reflectionV;

	reflectionV = multiv(surfaceNormal, dotv(surfaceNormal, surfaceToLight) * 2);
	return (subv(reflectionV, surfaceToLight));
}

vector	getSurfaceNormal(vector point, t_item *item)
{
	vector	surfaceNormal;

	if (item->t_type == SHPERE)
		surfaceNormal = subv(point, item->sphere.pos);
	else if (item->t_type == PLANE)
		surfaceNormal = item->plane.orientation;
	surfaceNormal = normalizev(surfaceNormal);
	return (surfaceNormal);
}

double	getLightAngle(vector oPoint, vector dir, t_rays ray, vector light, t_item *items)
{
	vector	point;
	vector	surfaceNormal;
	vector	surfaceToLight;
	t_item	*item = items;
	double	dist;
	double	distToLight;
	double	res;


	point = addv(oPoint, multiv(dir, ray.dist));
	surfaceToLight = normalizev(subv(light, point));
	if (ray.closestitem->t_type == PLANE && !checkSameSide(ray.closestitem->plane, oPoint, light))
		return (-1.0);	
	surfaceNormal = getSurfaceNormal(point, ray.closestitem);
	res = dotv(surfaceNormal, surfaceToLight);
	if (res > 0)
	{
		distToLight = getDistBetweenPoints(point, light);
		while (item)
		{
			if (item == ray.closestitem)
			{
				item = item->next;
				continue;
			}
			if (item->t_type == SHPERE)
				dist = hitSp(point, surfaceToLight, item->sphere);
			if (item->t_type == PLANE)
				dist = hitPl(point, surfaceToLight, item->plane);
			if (dist > 0 && dist < distToLight)
				return (-1.0);
			item = item->next;
		}
	}
	return (res);
}

int	computeColor(t_vars vars, t_rays ray)
{}

double	hitPl(vector origin, vector ray, t_plane plane)
{
	double	dist;
	double	denom;

	denom = dotv(plane.orientation, ray);
	if (denom > EPSILON || denom < (-1 * EPSILON))
	{
		dist = dotv(subv(plane.point, origin)  , plane.orientation) / denom;
		if (dist > 0 && dist < 2500)
			return dist;
	}
	return (-1.0);
}

void	updateRayDist(int screendim, int i, t_vars *vars, t_item *obj, t_rays *rays)
{
	int	j;
	double	dist;

	j = -1;
	while(++j < screendim)
	{
		if (obj->t_type == SHPERE)
			dist = hitSp(vars->cam->pos, vars->cam->dirvectors[i][j], obj->sphere);
		else if (obj->t_type == PLANE)
			dist = hitPl(vars->cam->pos, vars->cam->dirvectors[i][j], obj->plane);
		if (dist > 0 && ((rays + j)->dist == -1.0 || dist < (rays + j)->dist))
		{
			(rays + j)->dist = dist;
			(rays + j)->closestitem = obj;
		}
	}
}
