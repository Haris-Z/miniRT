/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:17:27 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 12:24:25 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "color.h"
# include "vec.h"

/**
 * @brief 
 * 
 */
typedef struct s_ray
{
	t_vec3	origin;		//
	t_vec3	direction;	//
}	t_ray;

// albedo 
// a measure of reflectivity
// include reflectivity,
// reflection coefficient, 
// reflectance,
// reflective power,
// and in digital art/rendering,
/// diffuse map or base color,
// all describing how much light a surface bounces back,
// with higher values meaning more reflection
// and lower values meaning more absorption.
typedef struct s_hit
{
	double	t;
	t_vec3	p;
	t_vec3	n;
	t_color	albedo; 
}	t_hit;

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