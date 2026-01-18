/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:53:27 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/18 05:23:03 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
// #include "rt.h"
#include "rt_error.h"
#include "scene.h"
#include "parser.h"

// LIGHT
// id	Pos			Brightness	Colors
// L	-40,0,30	0.7 		255,255,255
int	parse_light(t_scene *s, char **t)
{
	t_light	light;

	if (!t[1] || !t[2] || !t[3] || t[4])
		return (E_PARSE_FORMAT_L);
	if (parse_vec3(t[1], &light.pos) != 0)
		return(E_PARSE_BAD_VEC);
	if (parse_ratio(t[2], &light.bright) != 0)
		return (E_PARSE_BAD_RATIO);
	if (parse_color_vec(t[3], &light.color) != 0)
		return (E_PARSE_BAD_COLOR);
	light.rgb = color_to_int(light.color);
	if (scene_set_light(s, light) != 0)
		return (E_PARSE_DUPLICATE_L);
	return (0);
}















