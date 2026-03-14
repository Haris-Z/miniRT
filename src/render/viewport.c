/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:52:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:34:11 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mrt.h"

// t_cam_rt	cam_init(t_vec3 pos, t_vec3 orientation, int fov, int screendim[2])
// light color and dir vector has to be added, also ambient color, or amb.rgb, light.rgb is an int
t_cam_rt	cam_init(t_scene s) // take W/H from app.w - app.h - function checks boundaries and assigns correct w/h
{
	t_cam_rt	cam;

	cam = (t_cam_rt){0};
	cam.orientation = vec_norm(s.cam.dir);
	cam.pos = s.cam.pos;
	cam.fov = s.cam.fov_deg;
	return (cam);
}

static void	add_dir_vector(t_cam_rt *cam, double preCalc[3], int i)
{
	double	pre_rot_x;

	pre_rot_x = (cam->vp.focalLength * cos(preCalc[2])
			* sin((90.0 / RADIAN) - cam->vp.verRange)) - cam->vp.focusDist;
	cam->rays[i].direction.y = cam->vp.focalLength
		* sin(preCalc[2]) * sin((90.0 / RADIAN) - cam->vp.verRange);
	cam->rays[i].direction.z = cam->vp.focalLength
		* cos((90.0 / RADIAN) - cam->vp.verRange);
	cam->rays[i].direction.x = pre_rot_x * preCalc[1]
		- cam->rays[i].direction.y * preCalc[0];
	cam->rays[i].direction.y = pre_rot_x * preCalc[0]
		+ cam->rays[i].direction.y * preCalc[1];
	cam->rays[i].direction = vec_mul_m(cam->rays[i].direction,
			cam->vp.rotationM);
	cam->rays[i].direction = vec_norm(cam->rays[i].direction);
	cam->rays[i].dist = -1.0;
	cam->rays[i].closestitem = NULL;
	preCalc[2] += cam->vp.deltaHorAngle;
}

void	add_dir_vector_row(t_cam_rt *cam, int w)
{
	int		i;
	double	pre_calc[3];

	pre_calc[0] = sin(cam->vp.horOffset);
	pre_calc[1] = cos(cam->vp.horOffset);
	pre_calc[2] = cam->vp.horRange * -1;
	i = -1;
	while (++i < w)
		add_dir_vector(cam, pre_calc, i);
	cam->vp.verRange -= cam->vp.deltaVerRange;
}

static void	get_matrix(t_mat3 *mat, t_vec3 orientation)
{
	*mat = calc_rotation_matrix(vec_norm(vec3(orientation.y,
					-1 * orientation.x, 0)),
			atan(orientation.z
				/ sqrt((orientation.x * orientation.x)
					+ (orientation.y * orientation.y))));
}

int	dir_vector_init(t_cam_rt *cam, int w, int h)
{
	cam->rays = malloc(sizeof(t_ray) * w);
	if (!cam->rays)
		return (0);
	cam->vp.focalLength = (double)powf(180.0 / cam->fov, FOCAL_SCALE_EXP);
	cam->vp.horRange = asin(sin(cam->fov / (2 * RADIAN)) / cam->vp.focalLength);
	cam->vp.focusDist = (cos(cam->vp.horRange) * cam->vp.focalLength)
		- (cos(cam->fov / (RADIAN * 2)));
	cam->vp.deltaHorAngle = (2 * cam->vp.horRange) / w;
	if (fabs(cam->orientation.x) < EPSILON)
		cam->orientation.x += 2 * EPSILON;
	cam->vp.verRange = (cam->vp.horRange * SCREEN_HEIGHT) / SCREEN_WIDTH;
	cam->vp.deltaVerRange = (cam->vp.verRange * 2) / h;
	cam->vp.horOffset = atan2(cam->orientation.y, cam->orientation.x);
	get_matrix(&cam->vp.rotationM, cam->orientation);
	return (1);
}
