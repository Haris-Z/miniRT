/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:22:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 20:24:22 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_new(t_vec3 orig, t_vec3 dir)
{
	t_ray	r;

	r.origin = orig;
	r.direction = dir;
	return (r);
}

t_vec3	ray_at(t_ray r, double t)
{
	return (vec_add(r.origin, vec_scale(r.direction, t)));
}