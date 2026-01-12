/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:57:29 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:34:54 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "color.h"
# include "ray.h"

typedef struct s_hit
{
	t_vec3	p;
	t_vec3	n;
	double	t;
	double	u;
	double	v;
	int		front_face;
	t_color	color;
	t_color albedo;
}	t_hit;

// albedo 
// a measure of reflectivity
// include reflectivity,
// reflection coefficient, 
// reflectance,
// reflective power,
// and in digital rendering,
// diffuse map or base color,
// all describing how much light a surface bounces back,
// with higher values meaning more reflection
// and lower values meaning more absorption.

int	hit_sphere(t_sphere *sp, t_ray ray,
						double tmin, double tmax, t_hit *hit);
// int hit_plane();
// int hit_cylinder();
// int hit_scene_objects();

#endif //HIT_H