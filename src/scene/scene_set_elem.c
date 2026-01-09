/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_set_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:51:49 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 16:01:49 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
	minimal.rt
	ID	Ratio	Color
	A	0.9 	255,255,255

	Ratio: ambient lighting ratio in the range [0.0,1.0]
	Color: R, G, B colors in the range [0-255]

*/
int	scene_set_ambient(t_scene *s, t_ambient a)
{
	if (s->has_ambient)
		return (1);
	s->amb = a;
	s->has_ambient = 1;
	return (0);
}

/*
	minimal.rt
	ID	Position	Direction	FOV(in deg)
	C	0,-1,3		0,0,-1		70

	Position:	x, y, z coordinates of the viewpoint
	Direction:	3D normalized orientation vector,
				in the range [-1,1] for each x, y, z axis
	FOV:		Horizontal field of view in degrees
				in the range [0,180]
*/
int	scene_set_camera(t_scene *s, t_camera c)
{
	if (s->has_camera)
		return (1);
	s->cam = c;
	s->has_camera = 1;
	return (0);
}

/*
	minimal.rt
	ID	Position	Brightness	Colors
	L	5,5,5		0.8			0,255,255

	Position:	x, y, z coordinates of the light point
	Brightness:	the light brightness ratio
				in the range [0.0,1.0]
	Colors:		(unused in mandatory part) R, G, B colors
				in the range [0-255]:
*/
int	scene_set_light(t_scene *s, t_light l)
{
	if (s->has_light)
		return (1);
	s->light = l;
	s->has_light = 1;
	return (0);
}