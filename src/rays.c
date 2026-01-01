#include "../includes/mini.h"
double	hitSp(vector cam_pos, vector ray, t_item ball)
{

	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	distfar;
	double	distnear;

	a = dotv(ray, ray);
	b = -2.0 * dotv(ray, subv(cam_pos,ball.sphere.pos));
	c = dotv(subv(cam_pos,ball.sphere.pos), subv(cam_pos,ball.sphere.pos)) - ball.sphere.radius * ball.sphere.radius;
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

double	hitPl(vector cam_pos, vector ray, t_item plane)
{
	double	dist;
	double	denom;

	denom = dotv(plane.plane.orientation, ray);
	if (denom > EPSILON || denom < (-1 * EPSILON))
	{
		dist = dotv(subv(plane.plane.point, cam_pos)  , plane.plane.orientation) / denom;
		if (dist > 0 && dist < 2500)
			return dist;
	}
	return (-1.0);
}

void	updateRayDist(int screendim, int i, t_vars *vars, t_item *obj, t_rays	*rays)
{
	int	j;
	double	dist;

	j = -1;
	while(++j < screendim)
	{
		if (obj->t_type == SHPERE)
			dist = hitSp(vars->cam->pos, vars->cam->dirvectors[i][j], *obj);
		else if (obj->t_type == PLANE)
			dist = hitPl(vars->cam->pos, vars->cam->dirvectors[i][j], *obj);
		if (dist > 0 && ((rays + j)->dist == -1.0 || dist < (rays + j)->dist))
		{
			(rays + j)->dist = dist;
			(rays + j)->closestitem = obj;
		}
	}
}
