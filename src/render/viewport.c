/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:52:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 17:32:01 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mrt.h"

static void	add_dir_vector(t_camera *cam, double preCalc[3], int i)
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

void	add_dir_vector_row(t_camera *cam, int w)
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

int	dir_vector_init(t_camera *cam, int w, int h)
{
	cam->rays = malloc(sizeof(t_ray) * w);
	if (!cam->rays)
		return (0);
	cam->vp.focalLength = (double)powf(180.0 / cam->fov_deg, FOCAL_SCALE_EXP);
	cam->vp.horRange = asin(sin(cam->fov_deg
				/ (2 * RADIAN)) / cam->vp.focalLength);
	cam->vp.focusDist = (cos(cam->vp.horRange) * cam->vp.focalLength)
		- (cos(cam->fov_deg / (RADIAN * 2)));
	cam->vp.deltaHorAngle = (2 * cam->vp.horRange) / w;
	if (fabs(cam->dir.x) < EPSILON)
		cam->dir.x += 2 * EPSILON;
	cam->vp.verRange = (cam->vp.horRange * SCREEN_HEIGHT) / SCREEN_WIDTH;
	cam->vp.deltaVerRange = (cam->vp.verRange * 2) / h;
	cam->vp.horOffset = atan2(cam->dir.y, cam->dir.x);
	get_matrix(&cam->vp.rotationM, cam->dir);
	return (1);
}
