/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:02:44 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:47:19 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "libft.h"

static int	in_range(double x, double min, double max)
{
	return (x >= min && x <= max);
}

int	parse_unit_vec(t_vec3 v)
{
	double	len;

	if (!in_range(v.x, -1.0, 1.0)
		|| !in_range(v.y, -1.0, 1.0)
		|| !in_range(v.z, -1.0, 1.0))
		return (rt_error_msg("Camera direction out of range [-1..1]"));
	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < 1e-12)
		return (rt_error_msg("Camera direction cannot be zero"));
	if (fabs(len - 1.0) > 1e-3)
		return (rt_error_msg("Camera direction must be normalized"));
	return (0);
}

int	parse_fov(const char *tok, double *out)
{
	int	fov;

	if (parse_int(tok, &fov))
		return(rt_error_msg("Camera (C): invalid FOV"));
	if (fov < 0 || fov > 180)
		return(rt_error_msg("Camera (C): FOV out of range [0..180]"));
	*out = fov;
	return (0);
}

// id	Direction	Orientation		FOV in deg
// C	-50,0,20 	1,0,0			70
/* 
	[x] validate tok count
	[x] check pos vec
	[x] check orientation vec
	[x] check orientation vec components in range [-1, 1]
	[x] check oriantation vec normalized (len ~ 1)
	[x] check fov (int + range [0,180])
	[x] check dup/unique
*/
int	parse_camera(t_scene *s, char **t)
{
	t_camera	cam;

	ft_bzero(&cam, sizeof(cam));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (E_PARSE_FORMAT_C);
	if (parse_vec3(t[1], &cam.pos) != 0)
		return (E_PARSE_BAD_VEC);
	if (parse_vec3(t[2], &cam.dir) != 0)
		return(E_PARSE_BAD_VEC);
	if (parse_unit_vec(cam.dir) != 0)
		return (E_PARSE_BAD_VEC);
	if (parse_fov(t[3], &cam.fov_deg) != 0)
		return (E_PARSE_BAD_FOV);
	if (scene_set_camera(s, cam) != 0)
		return (E_PARSE_DUPLICATE_C);
	return (0);
}

