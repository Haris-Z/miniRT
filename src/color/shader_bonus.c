/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:48:09 by agara             #+#    #+#             */
/*   Updated: 2026/03/16 18:49:53 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"

// ambient : 0			-> itemColor	| userInput
// diffuse : ambient	-> itemColor	| lightAngle
// specular: diffuse	-> 255			| viewAngle

t_color	scale_color(t_color min, t_color max, double amount)
{
	t_color	res;

	res.x = ((max.x - min.x) * amount) + min.x;
	res.y = ((max.y - min.y) * amount) + min.y;
	res.z = ((max.z - min.z) * amount) + min.z;
	return (res);
}

t_color	mix_color(t_color ambient, t_color *diffuse, t_color *specular, int num)
{
	t_color	res_l;
	t_color	res;
	int		i;

	i = -1;
	res = color_rgb(0, 0, 0);
	while (++i < num)
	{
		res_l = vec_add(specular[i], diffuse[i]);
		res = vec_add(res, res_l);
	}
	res = vec_add(ambient, vec_scale(res, 1.0 / num));
	res.x = rt_clamp(res.x, 0.0, 1.0);
	res.y = rt_clamp(res.y, 0.0, 1.0);
	res.z = rt_clamp(res.z, 0.0, 1.0);
	return (res);
}

static void	compute_color_l(t_scene s, t_ray ray,
	t_color colors[2][MAX_LIGHTS], int i)
{
	double	light_angle;
	double	shining;
	t_vec3	point;
	t_vec3	surface_normal;
	t_vec3	reflection_v;

	light_angle = get_light_angle(s.cam.pos, ray, s.light[i].pos,
			s.objects_array, s.objects_len);
	if (light_angle < 0)
		shining = 1;
	else
	{
		colors[0][i] = scale_color(color_rgb(0, 0, 0), ray.closestitem->color,
				light_angle * s.light[i].bright);
		colors[0][i] = vec_mul(colors[0][i], s.light[i].color);
		point = vec_add(s.cam.pos, vec_scale(ray.direction, ray.dist));
		surface_normal = get_surface_normal(point,
				ray.direction, ray.closestitem);
		reflection_v = get_reflection_v(vec_norm(\
			vec_sub(s.light[i].pos, point)), surface_normal);
		shining = vec_dot(reflection_v, ray.direction);
	}
	if (shining < 0)
		colors[1][i] = scale_color(color_rgb(0, 0, 0), s.light[i].color,
				(double)powf(shining, SHINE) * s.light[i].bright);
}

t_color	compute_color(t_scene s, t_ray ray)
{
	t_color	ambient_color;
	int		i;
	t_color	colors[2][MAX_LIGHTS];

	ft_bzero(colors, sizeof(colors));
	ambient_color = scale_color(color_rgb(0, 0, 0),
			ray.closestitem->color, s.amb.ratio);
	ambient_color = vec_mul(ambient_color, s.amb.color);
	i = -1;
	while (++i < (int)s.light_count)
		compute_color_l(s, ray, colors, i);
	return (mix_color(ambient_color, colors[0], colors[1], s.light_count));
}
