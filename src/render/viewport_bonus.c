/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:52:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 17:32:22 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mrt.h"

t_ray	get_dir_vector(t_camera *cam, double preCalc[6])
{
	double	pre_rot_x;
	t_ray	res;

	pre_rot_x = (cam->vp.focal_l * cos(preCalc[3])
			* sin((90.0 / RADIAN) - preCalc[2])) - cam->vp.focus_dist;
	res.direction.y = cam->vp.focal_l
		* sin(preCalc[3]) * sin((90.0 / RADIAN) - preCalc[2]);
	res.direction.z = cam->vp.focal_l * cos((90.0 / RADIAN) - preCalc[2]);
	res.direction.x = pre_rot_x * preCalc[1] - res.direction.y * preCalc[0];
	res.direction.y = pre_rot_x * preCalc[0] + res.direction.y * preCalc[1];
	res.direction = vec_mul_m(res.direction, cam->vp.rotation_m);
	res.direction = vec_norm(res.direction);
	res.dist = -1.0;
	res.closestitem = NULL;
	return (res);
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
	cam->vp.focal_l = (double)powf(180.0 / cam->fov_deg, FOCAL_SCALE_EXP);
	cam->vp.hor_range = asin(sin(cam->fov_deg
				/ (2 * RADIAN)) / cam->vp.focal_l);
	cam->vp.focus_dist = (cos(cam->vp.hor_range) * cam->vp.focal_l)
		- (cos(cam->fov_deg / (RADIAN * 2)));
	cam->vp.delta_hor_angle = (2 * cam->vp.hor_range) / (w * MSAA);
	if (fabs(cam->dir.x) < EPSILON)
		cam->dir.x += 2 * EPSILON;
	cam->vp.ver_range = (cam->vp.hor_range * SCREEN_HEIGHT) / SCREEN_WIDTH;
	cam->vp.delta_ver_range = (cam->vp.ver_range * 2) / (h * MSAA);
	cam->vp.hor_offset = atan2(cam->dir.y, cam->dir.x);
	get_matrix(&cam->vp.rotation_m, cam->dir);
	return (1);
}
