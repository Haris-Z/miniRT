/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:22:49 by agara             #+#    #+#             */
/*   Updated: 2026/02/08 19:22:58 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

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

t_color	compute_color(t_rt_mlx vars, t_ray ray, t_obj **items)
{
	t_color	ambient_color;
	t_color	diffuse_color;
	double	light_angle;

	ambient_color = scale_color(color_rgb(0, 0, 0),
			ray.closestitem->color, vars.cam.ambient.ratio);
	light_angle = get_light_angle(vars.cam.pos,
			ray, vars.cam.light.pos, *items);
	if (light_angle < 0)
		return (ambient_color);
	diffuse_color = scale_color(ambient_color,
			ray.closestitem->color, light_angle * vars.cam.light.bright);
	return (diffuse_color);
}

/*
**
** PREVIOUS WITH LIST
**
*/
// t_color	compute_color(t_rt_mlx vars, t_ray ray, t_obj **items)
// {
// 	t_color	ambient_color;
// 	t_color	diffuse_color;
// 	double	light_angle;

// 	ambient_color = scale_color(color_rgb(0, 0, 0),
// 			ray.closestitem->color, vars.cam.ambient);
// 	light_angle = get_light_angle(vars.cam.pos,
// 			ray, vars.cam.light.pos, *items);
// 	if (light_angle < 0)
// 		return (ambient_color);
// 	diffuse_color = scale_color(ambient_color,
// 			ray.closestitem->color, light_angle * vars.cam.light.bright);
// 	return (diffuse_color);
// }