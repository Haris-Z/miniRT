/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:16:29 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/28 23:16:31 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_mat3	mat_new(t_vec3 colx, t_vec3 coly, t_vec3 colz)
{
	t_mat3	res;

	res.colx = colx;
	res.coly = coly;
	res.colz = colz;
	return (res);
}

t_mat3	mat_mult(t_mat3 a, t_mat3 b)
{
	t_mat3	res;

	res.colx.x = a.colx.x * b.colx.x + a.coly.x
		* b.colx.y + a.colz.x * b.colx.z;
	res.colx.y = a.colx.y * b.colx.x + a.coly.y
		* b.colx.y + a.colz.y * b.colx.z;
	res.colx.z = a.colx.z * b.colx.x + a.coly.z
		* b.colx.y + a.colz.z * b.colx.z;
	res.coly.x = a.colx.x * b.coly.x + a.coly.x
		* b.coly.y + a.colz.x * b.coly.z;
	res.coly.y = a.colx.y * b.coly.x + a.coly.y
		* b.coly.y + a.colz.y * b.coly.z;
	res.coly.z = a.colx.z * b.coly.x + a.coly.z
		* b.coly.y + a.colz.z * b.coly.z;
	res.colz.x = a.colx.x * b.colz.x + a.coly.x
		* b.colz.y + a.colz.x * b.colz.z;
	res.colz.y = a.colx.y * b.colz.x + a.coly.y
		* b.colz.y + a.colz.y * b.colz.z;
	res.colz.z = a.colx.z * b.colz.x + a.coly.z
		* b.colz.y + a.colz.z * b.colz.z;
	return (res);
}

t_mat3	mat_scale(double amount, t_mat3 mat)
{
	t_mat3	res;

	res.colx = vec_scale(mat.colx, amount);
	res.coly = vec_scale(mat.coly, amount);
	res.colz = vec_scale(mat.colz, amount);
	return (res);
}

t_mat3	mat_add(t_mat3 a, t_mat3 b)
{
	t_mat3	res;

	res.colx = vec_add(a.colx, b.colx);
	res.coly = vec_add(a.coly, b.coly);
	res.colz = vec_add(a.colz, b.colz);
	return (res);
}

t_mat3	calc_rotation_matrix(t_vec3 axis, double verAngle)
{
	t_mat3	res;
	t_mat3	i;
	t_mat3	cross_m;

	i = mat_new(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
	cross_m = mat_new(vec3(0, axis.z, -1 * axis.y),
			vec3(-1 * axis.z, 0, axis.x), vec3(axis.y, -1 * axis.x, 0));
	res = mat_add(i, mat_scale(sin(verAngle), cross_m));
	res = mat_add(res, mat_scale(1 - cos(verAngle),
				mat_mult(cross_m, cross_m)));
	return (res);
}
