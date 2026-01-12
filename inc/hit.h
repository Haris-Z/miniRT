/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:57:29 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 14:06:52 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "color.h"
# include "ray.h"
# include "scene.h"

# define TMIN 1e-4
# define TMAX 1e30

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

// int hit_plane();
// int hit_cylinder();
// int hit_scene_objects();
int	hit_sphere(t_sphere *sp, t_ray ray, double tmin, double tmax, t_hit *hit);
int	hit_scene_objs(t_scene *s, t_ray r, double tmin, double tmax, t_hit *h);

// not in use currently - refctoring
// int	hit_get_sphere_intersection(t_sphere *sp, t_ray ray, t_hit *hit, double tmax);
// int	hit_get_scene_objs_intersection(t_scene *s, t_ray r, t_hit *h, double tmax);

// not in use currently - refactoring
// utils
t_vec3	hit_get_sphere_normal(t_vec3 center, double radius, t_vec3 h_point);
t_color	hit_get_shade(t_scene *s, t_hit hit, t_color albedo);

#endif //HIT_H