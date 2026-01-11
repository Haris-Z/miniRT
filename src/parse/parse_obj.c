/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:11:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/11 10:20:09 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"
#include "rt_error.h"

// id	center	diameter		color
// sp	0,0,20	12.6			255,0,0
int	parse_sphere(t_scene *s, char **t)
{
	t_sphere	sp;

	if (!t[1] || !t[2] || !t[3] || t[4])
		return(rt_error_msg("Sphere (sp): expected 'sp x,y,z diameter R,G,B'"));
	if (parse_vec3(t[1], &sp.center) != 0)
		return(rt_error_msg("Invalid vector for Sphere (sp) center"));
	if (parse_double(t[2], &sp.diameter) != 0 || sp.diameter <= 0.0)
		return(rt_error_msg("Sphere (sp): diameter must be > 0"));
	sp.radius = sp.diameter * 0.5;
	if (parse_color_vec(t[3], &sp.color) != 0 )
		return(rt_error_msg("Sphere (sp): rgb invalid/out of range"));
	if (scene_add_sphere(s, sp) != 0)
		return (1);
	return (0);
}