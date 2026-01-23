/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:18:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/23 17:45:40 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "math.h"

// shading color calc - value should be [0,1] - restrict to stay between 0/1
// avoid overflow underflow when converting
// example clamp(1.2, 0.0,1.0) = 1
// example clamp(-0.2, 0.0, 1.0) = 0
// multiple lights maybe?
double	rt_clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

// turn float into integer in range [0,255] + rounding
// round to nearest instead of truncating
// x = 0.0 → 0
// x = 1.0 → 255
// x = 0.5 → 128 (0.5*255 = 127.5, +0.5 → 128.0)
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

// get normalized color for easy calculations with
// vec operations
// olor_rgb(255, 0, 128)
t_color	color_rgb(int r, int g, int b)
{
	return (vec3(
			(double)r / 255.0,
			(double)g / 255.0,
			(double)b / 255.0));
}

/* MLX expects 0x00RRGGBB */
// each float to byte - 
// then pack
// r into biits 16-23
// b into bits 8-15
// g into bits 0-7
// r = 255, g = 128, b = 0
// -> (255<<16) | (128<<8) | 0 ----> 0x00FF8000
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
// same as clamp but per color channel with math func and at once
// works on doubles , can be used in shading for example
t_color	color_normalize(t_color c)
{
	t_color	result;
	
	result.x = fmin(fmax(c.x, 0.0), 1.0);
	result.y = fmin(fmax(c.y, 0.0), 1.0);
	result.z = fmin(fmax(c.z, 0.0), 1.0);
	return (result);
}

// same like color to mlx
// uses truncating instead of rounding
// c.x == 1.0, ---> 255.999 * 1.0 = 255.99 --> = 255 
int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;
	
	c = color_normalize(c);
	r = (int)(255.999 * c.x);
	g = (int)(255.999 * c.y);
	b = (int)(255.999 * c.z);
	return ((r << 16) | (g << 8) | b);
}