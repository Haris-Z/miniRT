#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct vector
{
	double	x;
	double	y;
	double	z;
}				 vector;


vector	addv(vector a, vector b);
vector	subv(vector a, vector b);
vector	multiv(vector a, double num);
double	dotv(vector a, vector b);
vector	crossv(vector a, vector b);
vector	normalizev(vector a);
void	printV(vector v);

#endif
