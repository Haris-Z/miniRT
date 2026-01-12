/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:05:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:52:27 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cam.h"

// mamp pixel to vp
static void	pixel_to_viewport(t_cam_rt cam, int px, int py, double *u, double *v)
{
	*u = (((double)px + 0.5) / (double)cam.w - 0.5) * cam.w_viewport;
	*v = (0.5 - ((double)py + 0.5) / (double)cam.h) * cam.h_viewport;
}

// get ray direction 
static t_vec3	compute_ray_dir(t_cam_rt cam, double u, double v)
{
	t_vec3	dir;

	dir = vec_add(cam.forward, vec_scale(cam.right, u));
	dir = vec_add(dir, vec_scale(cam.up, v));
	return (vec_norm(dir));
}

// ray gen func
t_ray	cam_generate_ray(t_cam_rt cam, int px, int py)
{
	t_ray	ray;
	double	u; // init
	double	v; // init

	pixel_to_viewport(cam, px, py, &u, &v);
	ray.origin = cam.origin;
	ray.direction = compute_ray_dir(cam, u, v);
	ray.t = 0.0;
	return (ray);
}