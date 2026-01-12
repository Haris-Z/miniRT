/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:17:27 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:38:11 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "color.h"
# include "vec.h"

/**
 * @brief
 * 
 * @note P(t) = O + t·D, where t ≥ 0
 * 
 */
typedef struct s_ray
{
	t_vec3	origin;		// origin-point O = (ox,oy,oz)
	t_vec3	direction;	// dir-vector   D = vec_norm(dx, dy, dz);
	double	t;			// distance along the ray
}	t_ray;

/**
 * @brief 
 * 
 * @param orig 
 * @param dir 
 * @return t_ray 
 */
t_ray	ray_new(t_vec3 orig, t_vec3 dir);

/**
 * @brief 
 * 
 * @param r 
 * @param t 
 * @return t_vec3 
 */
t_vec3	ray_at(t_ray r, double t);

#endif // RAY_H