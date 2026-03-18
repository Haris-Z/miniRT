/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:18:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:45:39 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

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
