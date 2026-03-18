/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:33:29 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:14:37 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

// ----------- VECTOR -----------
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// ----------- MATRIX -----------
typedef struct s_mat3
{
	t_vec3	colx;
	t_vec3	coly;
	t_vec3	colz;
}	t_mat3;

/// basic vector operations
t_vec3		vec3(double x, double y, double z);
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_neg(t_vec3 v);
t_vec3		vec_scale(t_vec3 v, double s);
t_vec3		vec_mul(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
t_vec3		vec_norm(t_vec3 v);
double		vec_len(t_vec3 v);
double		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		vec_mul_m(t_vec3 v, t_mat3 m);

/// vector utils
int			vec_near_zero(t_vec3 v);
t_vec3		vec_reflect(t_vec3 v, t_vec3 n);
double		get_dist_between_p(t_vec3 pointA, t_vec3 pointB);
t_vec3		reject_axis(t_vec3 v, t_vec3 axis);

/// matrix ops
t_mat3		mat_new(t_vec3 colx, t_vec3 coly, t_vec3 colz);
t_mat3		mat_mult(t_mat3 a, t_mat3 b);
t_mat3		mat_scale(double amount, t_mat3 mat);
t_mat3		mat_add(t_mat3 a, t_mat3 b);
t_mat3		calc_rotation_matrix(t_vec3 axis, double verAngle);

#endif
