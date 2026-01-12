/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:18:09 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 12:58:56 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "hit.h"
#include "scene.h"
#include "vec.h"
#include <math.h>

static t_color	calc_diffuse(t_scene *s, t_vec3 point,
							t_vec3 normal, t_color albedo)
{
	t_vec3	light_dir;
	double	ndotl;
	double	intensity;
	
	if (!s->has_light)
		return ((t_color){0.0, 0.0, 0.0});
	light_dir = vec_norm(vec_sub(s->light.pos, point));
	ndotl = fmax(0.0, vec_dot(normal, light_dir));//
	intensity = s->light.bright * ndotl;
	return (vec_scale(albedo, intensity));
}

// ambient: albedo * amb.color * amb.ratio
static t_color	calc_ambient(t_scene *s, t_color albedo)
{
	if (!s->has_ambient)
		return ((t_color){0.0, 0.0, 0.0});
	return (vec_scale(vec_mul(albedo, s->amb.color), s->amb.ratio));
}


t_vec3	hit_get_sphere_normal(t_vec3 center, double radius, t_vec3 h_point)
{
	return (vec_scale(vec_sub(h_point, center), 1.0 / radius));
}

t_color	hit_get_shade(t_scene *s, t_hit hit, t_color albedo)
{
	t_color	final;
	t_color	ambient;
	t_color	diffuse;

	ambient = calc_ambient(s, albedo);
	diffuse = calc_diffuse(s, hit.p, hit.n, albedo);
	final = vec_add(ambient, diffuse);
	return (final);
}

// if the ray starts inside a sphere/cylinder, 
// the geometric normal still points "outward",
// but for shading you usually
// want the normal that points against the incoming ray 
// so your lighting doesn’t invert.
// void	hit_set_face_normal(t_hit *h, t_ray r, t_vec3 outward)
// {
// 	if (vec_dot(r.dir, outward) < 0.0)
// 	{
// 		h->front_face = 1;
// 		h->n = outward;
// 	}
// 	else
// 	{
// 		h->front_face = 0;
// 		h->n = vec_neg(outward);
// 	}
// }