#include "vector.h"

t_vec3 addv(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	subv(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3 multiv(t_vec3 a, double num)
{
	t_vec3	res;

	res.x = a.x * num;
	res.y = a.y * num;
	res.z = a.z * num;
	return (res);
}

double dotv(t_vec3 a, t_vec3 b)
{
	double	res;

	res = a.x * b.x;
	res += a.y * b.y;
	res += a.z * b.z;
	return (res);
}

t_vec3	normalizev(t_vec3 a)
{
	double	magnitude;
	t_vec3	res;

	magnitude = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	res.x = a.x / magnitude;
	res.y = a.y / magnitude;
	res.z = a.z / magnitude;
	return (res);
}

t_vec3 crossv(t_vec3 a, t_vec3 b)
{
	t_vec3 r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return r;
}

// vector crossv(vector a, vector b)
// {
// 	vector	res;

// 	res.x = a.y * b.y - a.z * b.y;
// 	res.y = a.z * b.x - a.x * b.z;
// 	res.z = a.x * b.y - a.y * b.x;
// 	return (res);
// }

double	getDistBetweenPoints(t_vec3 pointA, t_vec3 pointB)
{
	double	res;

	res = pow(pointA.x - pointB.x, 2) +
		pow(pointA.y - pointB.y, 2) +
		pow(pointA.z - pointB.z, 2);
	return (sqrt(res));
}

#include <stdio.h>
void	printV(t_vec3 v)
{
	printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);
}