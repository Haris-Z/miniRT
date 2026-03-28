/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:11:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/28 23:19:51 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"
#include "rt_error.h"

// id	center	diameter		color
// sp	0,0,20	12.6			255,0,0
int	parse_sphere(t_scene *s, char **t)
{
	t_sphere	sp;
	int			err;

	ft_bzero(&sp, sizeof(sp));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (RT_ERR_FORMAT);
	err = parse_vec3(t[1], &sp.center);
	if (err != RT_SUCCESS)
		return (err);
	if (ft_strtod(t[2], &sp.diameter) != 0)
		return (RT_ERR_BAD_FLOAT);
	if (sp.diameter <= 0.0)
		return (RT_ERR_DIAMETER);
	sp.radius = sp.diameter * 0.5;
	err = parse_color_vec(t[3], &sp.color);
	if (err != RT_SUCCESS)
		return (err);
	if (scene_add_sphere(s, sp) != 0)
		return (RT_ERR_MALLOC);
	return (0);
}

// id	point		normal		color
// pl	0,-2,0		0,1,0		200,200,200
int	parse_plane(t_scene *s, char **t)
{
	t_plane	pl;
	int		err;

	ft_bzero(&pl, sizeof(pl));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (RT_ERR_FORMAT);
	err = parse_vec3(t[1], &pl.point);
	if (err != 0)
		return (err);
	err = parse_unit_vec3(t[2], &pl.normal);
	if (err != 0)
		return (err);
	err = parse_color_vec(t[3], &pl.color);
	if (err != 0)
		return (err);
	if (scene_add_plane(s, pl) != 0)
		return (RT_ERR_MALLOC);
	return (0);
}

// // id	center		axis	diameter	height	color
// // cy	2,0,0		0,1,0	1			3		0,0,255
int	parse_cylinder(t_scene *s, char **t)
{
	t_cylinder	cy;
	int			err;

	ft_bzero(&cy, sizeof(cy));
	if (!t[1] || !t[2] || !t[3] || !t[4] || !t[5] || t[6])
		return (RT_ERR_FORMAT);
	err = parse_vec3(t[1], &cy.center);
	if (err != 0)
		return (err);
	err = parse_unit_vec3(t[2], &cy.axis);
	if (err != 0)
		return (err);
	if (ft_strtod(t[3], &cy.diameter) != 0)
		return (RT_ERR_BAD_FLOAT);
	if (cy.diameter <= 0.0)
		return (RT_ERR_DIAMETER);
	cy.radius = cy.diameter * 0.5;
	if (ft_strtod(t[4], &cy.height) != 0)
		return (RT_ERR_BAD_FLOAT);
	if (cy.height <= 0.0)
		return (RT_ERR_HEIGHT);
	err = parse_color_vec(t[5], &cy.color);
	if (err != 0)
		return (err);
	if (scene_add_cylinder(s, cy) != 0)
		return (RT_ERR_MALLOC);
	return (0);
}
