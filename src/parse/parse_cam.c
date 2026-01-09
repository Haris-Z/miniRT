/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:02:44 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 14:43:26 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include "rt_error.h"
#include "scene.h"
#include "parser.h"
#include "libft.h"

static int	in_range(double x, double min, double max)
{
	return (x >= min && x <= max);
}

int	parse_unit_vec(t_vec3 v)
{
	double	len;

	if (!in_range(v.x, -1.0, 1.0) || !in_range(v.y, -1.0, 1.0)
		|| !in_range(v.z, -1.0, 1.0))
		return(rt_error_msg("Unit vector components out of range [-1..1] for Camera orientation (C)"));
	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < 1e-12)
		return(rt_error_msg("Unit vector is zero fo for Camera orientation (C)"));
	if (fabs(len - 1.0) > 1e-3)
		return(rt_error_msg("Vector must be normalized for Camera orientation (C)"));
	return (0);
}

int	parse_fov(const char *tok, double *out)
{
	int	f;

	if (parse_int(tok, &f))
		return(rt_error_msg("Camera (C): invalid FOV"));
	if (f < 0.0 || f > 180.0)
		return(rt_error_msg("Camera (C): FOV out of range [0..180]"));
	*out = f;
	return (0);
}

// id	Direction	Orientation		FOV in deg
// C	-50,0,20 	1,0,0			70
int	parse_camera(t_scene *s, char **t)
{
	t_camera	cam;

	ft_bzero(&cam, sizeof(cam));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return(rt_error_msg("Camera (C): expected 'C x,y,z nx,ny,nz fov'"));
	if (parse_vec3(t[1], &cam.pos) != 0)
		return(rt_error_msg("Invalid vec for Camera position (C)"));
	if (parse_vec3(t[2], &cam.dir) != 0)
		return(rt_error_msg("Invalid vec for Camera orientation (C)"));
	if (parse_unit_vec(cam.dir) != 0)
		return (1);
	if (parse_fov(t[3], &cam.fov_deg) != 0)
		return (1);
	if (scene_set_camera(s, cam) != 0)
		return(rt_error_msg("Duplicate camera (C)"));
	return (0);
}
