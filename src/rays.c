#include "../includes/mini.h"

double	hitSp(vector ray, t_item ball)
{

	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dotv(ray, ray);
	b = -2.0 * dotv(ray, ball.pos);
	c = dotv(ball.pos, ball.pos) - ball.radius * ball.radius;
	discriminant = (b*b - 4*a*c);
	if (discriminant < 0)
		return -1.0;
	else {
		return (-b - sqrt(discriminant) ) / (2.0*a);
	}
}


void	updateRayDist(int screendim, int i, t_vars *vars, t_item *obj, t_rays	*rays)
{
	int	j;
	double	dist;

	j = -1;
	while(++j < screendim)
	{
		dist = hitSp(vars->cam->dirvectors[i][j], *obj);
		if (dist != -1.0 && ((rays + j)->dist == -1.0 || dist < (rays + j)->dist))
		{
			(rays + j)->dist = dist;
			(rays + j)->closestitem = obj;
		}
	}
}
