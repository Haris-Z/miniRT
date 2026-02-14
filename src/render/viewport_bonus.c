/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:52:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/08 19:18:24 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mrt.h"

// t_cam_rt	cam_init(t_vec3 pos, t_vec3 orientation, int fov, int screendim[2])
// light color and dir vector has to be added, also ambient color, or amb.rgb, light.rgb is an int
t_cam_rt	cam_init(t_scene s, int w, int h)
{
	t_cam_rt	cam = {0};

	cam.orientation = vec_norm(s.cam.dir);
	cam.pos = s.cam.pos;
	cam.pixels[0] = w;
	cam.pixels[1] = h;
	cam.ambient = s.amb;
	cam.fov = s.cam.fov_deg;
	cam.light = s.light;
	return (cam);
}

t_ray	get_dir_vector(t_cam_rt *cam, double preCalc[4])
{
	double	pre_rot_x;
	t_ray	res;

	pre_rot_x = (cam->vp.focalLength * cos(preCalc[3])
			* sin((90.0 / RADIAN) - preCalc[2])) - cam->vp.focusDist;
	res.direction.y = cam->vp.focalLength	* sin(preCalc[3]) * sin((90.0 / RADIAN) - preCalc[2]);
	res.direction.z = cam->vp.focalLength	* cos((90.0 / RADIAN) - preCalc[2]);
	res.direction.x = pre_rot_x * preCalc[1] - res.direction.y * preCalc[0];
	res.direction.y = pre_rot_x * preCalc[0] + res.direction.y * preCalc[1];
	res.direction = vec_mul_m(res.direction, cam->vp.rotationM);
	res.direction = vec_norm(res.direction);
	res.dist = -1.0;
	res.closestitem = NULL;
	return (res);
}

// void	add_dir_vector_row(t_cam_rt *cam)
// {
// 	int		i;
// 	i = -1;
// 	while (++i < cam->pixels[0])
// 		add_dir_vector(cam, pre_calc, i);
//	cam->vp.verRange -= cam->vp.deltaVerRange;
// }

static void	get_matrix(t_mat3 *mat, t_vec3 orientation)
{
	*mat = calc_rotation_matrix(vec_norm(vec3(orientation.y,
					-1 * orientation.x, 0)),
			atan(orientation.z
				/ sqrt((orientation.x * orientation.x)
					+ (orientation.y * orientation.y))));
}

int	dir_vector_init(t_cam_rt *cam)
{
	// cam->focalLength = (double)powf(180.0 / cam->fov, 2);
	cam->vp.focalLength = 180.0 / cam->fov;
	cam->vp.horRange = asin(sin(cam->fov / (2 * RADIAN)) / cam->vp.focalLength);
	cam->vp.focusDist = (cos(cam->vp.horRange) * cam->vp.focalLength)
		- (cos(cam->fov / (RADIAN * 2)));
	cam->vp.deltaHorAngle = (2 * cam->vp.horRange) / (cam->pixels[0] * MSAA);
	if (fabs(cam->orientation.x) < EPSILON)
		cam->orientation.x += 2 * EPSILON;
	cam->vp.verRange = (cam->vp.horRange * SCREEN_HEIGHT) / SCREEN_WIDTH;
	cam->vp.deltaVerRange = (cam->vp.verRange * 2) / (cam->pixels[1] * MSAA);
	cam->vp.horOffset = -1.0 * atan(cam->orientation.y / cam->orientation.x);
	get_matrix(&cam->vp.rotationM, cam->orientation);
	return (1);
}
