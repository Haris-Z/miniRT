/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:11:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/18 05:29:39 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"
#include "libft.h"
#include "rt_error.h"

// id	center	diameter		color
// sp	0,0,20	12.6			255,0,0
int	parse_sphere(t_scene *s, char **t)
{
	t_sphere	sp;

	ft_bzero(&sp, sizeof(sp));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return(E_PARSE_FORMAT_SP);
	if (parse_vec3(t[1], &sp.center) != 0)
		return(rt_error_log(E_PARSE_BAD_VEC, "Invalid vector for Sphere (sp) center", 0, NULL));
	if (parse_double(t[2], &sp.diameter) != 0 || sp.diameter <= 0.0)
		return(rt_error_log(E_PARSE_BAD_FLOAT, "Sphere (sp): diameter must be > 0", 0, NULL));
	sp.radius = sp.diameter * 0.5;
	if (parse_color_vec(t[3], &sp.color) != 0 )
		return(rt_error_log(E_PARSE_BAD_COLOR, "Sphere (sp): rgb invalid/out of range", 0, NULL));
	if (scene_add_sphere(s, sp) != 0)
		return (E_SYS);
	return (0);
}

int	parse_plane(t_scene *s, char **t)
{
	t_plane	pl;

	ft_bzero(&pl, sizeof(pl));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return(E_PARSE_FORMAT_PL);
	if (parse_vec3(t[1], &pl.point) != 0)
	{
		rt_error_msg("Invalid vector for Plane point (pl)");
		return(E_PARSE_BAD_VEC);
	}
	if (parse_vec3(t[2], &pl.normal) != 0)
	{
		rt_error_msg("Invalid vector for Plane normal (pl)");
		return(E_PARSE_BAD_VEC);
	}
	if (parse_unit_vec(pl.normal) != 0)
		return(rt_error_msg("Invaldi unit vector for Plane normal (pl)"));
	if (parse_color_vec(t[3], &pl.color) != 0)
		return(rt_error_msg("Plane color (pl) : rgb invalid / out of range"));
	if (scene_add_plane(s, pl) != 0)
		return (E_SYS);
	return (0);
}

int	parse_cylinder(t_scene *s, char **t)
{
	t_cylinder	cy;

	ft_bzero(&cy, sizeof(cy));
	if (!t[1] || !t[2] || !t[3] || !t[4] || !t[5] || t[6])
		return (E_PARSE_FORMAT_CY);
	if (parse_vec3(t[1], &cy.center) != 0)
		return (rt_error_msg("Invalid vector for Cylinder (cy) center"));
	if (parse_vec3(t[2], &cy.axis) != 0)
		return (rt_error_msg("Invalid vector for Cylinder (cy) axis"));
	if (parse_unit_vec(cy.axis) != 0)
		return (rt_error_msg("Invalid unit vector for Cylinder (cy) axis"));
	if (parse_double(t[3], &cy.diameter) != 0 || cy.diameter <= 0.0)
		return (rt_error_msg("Cylinder (cy): diameter must be > 0"));
	if (parse_double(t[4], &cy.height) != 0 || cy.height <= 0.0)
		return (rt_error_msg("Cylinder (cy): height must be > 0"));
	if (parse_color_vec(t[5], &cy.color) != 0)
		return (rt_error_msg("Cylinder (cy): rgb invalid/out of range"));
	if (scene_add_cylinder(s, cy) != 0)
		return (E_SYS);
	return (0);
}
