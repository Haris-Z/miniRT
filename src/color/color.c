/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:18:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 20:19:42 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

double	rt_clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

t_color	color_rgb(int r, int g, int b)
{
	return (vec3(
			(double)r / 255.0,
			(double)g / 255.0,
			(double)b / 255.0));
}

static int	to_byte(double x)
{
	int	v;

	x = rt_clamp(x, 0.0, 1.0);
	v = (int)(x * 255.0 + 0.5);
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

/* MLX expects 0x00RRGGBB */
int	color_to_mlx(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = to_byte(c.x);
	g = to_byte(c.y);
	b = to_byte(c.z);
	return ((r << 16) | (g << 8) | b);
}