#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "vec.h"

t_vec3	addv(t_vec3 a, t_vec3 b);
t_vec3	subv(t_vec3 a, t_vec3 b);
t_vec3	multiv(t_vec3 a, double num);
double	dotv(t_vec3 a, t_vec3 b);
t_vec3	crossv(t_vec3 a, t_vec3 b);
t_vec3	normalizev(t_vec3 a);
void	printV(t_vec3 v);
double	getDistBetweenPoints(t_vec3 pointA, t_vec3 pointB);

#endif
