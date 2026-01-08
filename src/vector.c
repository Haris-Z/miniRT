#include "../includes/vector.h"

vector addv(vector a, vector b)
{
	vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

vector	subv(vector a, vector b)
{
	vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

vector multiv(vector a, double num)
{
	vector	res;

	res.x = a.x * num;
	res.y = a.y * num;
	res.z = a.z * num;
	return (res);
}

double dotv(vector a, vector b)
{
	double	res;

	res = a.x * b.x;
	res += a.y * b.y;
	res += a.z * b.z;
	return (res);
}

vector	normalizev(vector a)
{
	double	magnitude;
	vector	res;

	magnitude = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	res.x = a.x / magnitude;
	res.y = a.y / magnitude;
	res.z = a.z / magnitude;
	return (res);
}

vector crossv(vector a, vector b)
{
	vector	res;

	res.x = a.y * b.y - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

#include <stdio.h>
void	printV(vector v)
{
	printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);
}