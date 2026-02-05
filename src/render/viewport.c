/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:52:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/05 20:31:11 by agara            ###   ########.fr       */
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
	cam.ambient = s.amb.ratio;
	cam.fov = s.cam.fov_deg;
	cam.light = s.light;
	return (cam);
} 

void	add_dir_vector_row(t_cam_rt *cam)
{
	int		i;
	double	horAngle;
	double	preRotX;
	double	sinOffset;
	double	cosOffset;

	sinOffset = sin(cam->horOffset);
	cosOffset = cos(cam->horOffset);
	horAngle = cam->horRange;
	i = -1;
	while(++i < cam->pixels[0])
	{
		preRotX = (cam->focalLength * cos(horAngle) * sin((90.0/RADIAN) - cam->verRange)) - cam->focusDist;
		cam->rays[i].direction.y = cam->focalLength * sin(horAngle) * sin((90.0/RADIAN) - cam->verRange);
		cam->rays[i].direction.z = cam->focalLength * cos((90.0/RADIAN) - cam->verRange);
 		cam->rays[i].direction.x = preRotX * cos(cam->horOffset) - cam->rays[i].direction.y * sin(cam->horOffset);	//rotation around cam
 		cam->rays[i].direction.y = preRotX * sin(cam->horOffset) + cam->rays[i].direction.y * cos(cam->horOffset);
		cam->rays[i].direction = vec_mul_M(cam->rays[i].direction, cam->rotationM);
		cam->rays[i].direction = vec_norm(cam->rays[i].direction);
		cam->rays[i].dist = -1.0;
		cam->rays[i].closestitem = NULL;
		horAngle -= cam->deltaHorAngle;
	}
	cam->verRange -= cam->deltaVerRange;
}

int	dir_vector_init(t_cam_rt *cam)
{
	cam->rays = malloc(sizeof(t_ray) * cam->pixels[0]);
	if (!cam->rays)
		return (0);
	// cam->focalLength = (double)powf(180.0 / cam->fov, 2);
	cam->focalLength = 180.0 / cam->fov;
	cam->horRange = asin(sin(cam->fov / (2 * RADIAN)) / cam->focalLength);
	cam->focusDist = (cos(cam->horRange) * cam->focalLength) - (cos(cam->fov / (RADIAN * 2)));
	cam->deltaHorAngle = (2 * cam->horRange) / cam->pixels[0];
	if (fabs(cam->orientation.x) < EPSILON)
		cam->orientation.x += 2 * EPSILON;
	cam->verRange = (cam->horRange * SCREEN_HEIGHT) / SCREEN_WIDTH;
	cam->deltaVerRange =  (cam->verRange * 2) / cam->pixels[1];
	cam->horOffset = -1.0 * atan(cam->orientation.y / cam->orientation.x);
	printf("flen %f verRange %f deltahightsum %f deltahorsum %f width %f\n",cam->focalLength,cam->verRange * RADIAN, cam->deltaVerRange * cam->pixels[1] * RADIAN,cam->deltaHorAngle * cam->pixels[0] * RADIAN, cam->horRange * RADIAN);
	cam->rotationM = calcRotationMatrix(vec_norm(vec3(cam->orientation.y, -1 * cam->orientation.x, 0)),
		atan(cam->orientation.z / sqrt((cam->orientation.x * cam->orientation.x) + (cam->orientation.y * cam->orientation.y))));
	return (1);
}
