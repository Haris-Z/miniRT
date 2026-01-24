/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:52:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 12:52:48 by hazunic          ###   ########.fr       */
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
	cam.light = s.light.pos;
	return (cam);
} 

void	addDirVectorRow(t_cam_rt *cam)
{
	int	i;

	i = -1;
	while(++i < cam->pixels[0])
	{
		cam->xyTemplate[i].z = cam->height;
		cam->xyTemplate[i] = vec_norm(cam->xyTemplate[i]);
		cam->rays[i].direction = vec_mul_M(cam->xyTemplate[i], cam->rotationM);
		cam->rays[i].dist = -1.0;
		cam->rays[i].closestitem = NULL;
	}
	cam->height -= cam->deltaHeight;
}


void	createXYTemplate(t_cam_rt *cam)
{
	int	i;
	double	sinOffset;
	double	cosOffset;
	double	horOffset;
	double	preRotX;
	
	horOffset = atan(cam->orientation.y / cam->orientation.x);
	sinOffset = sin(horOffset);
	cosOffset = cos(horOffset);
	i = -1;
	while(++i < cam->pixels[0])
	{
		preRotX = (cos(cam->horRange) * cam->focalLength) - cam->focusDist;				//rotation around focuspoint
		cam->xyTemplate[i].y = sin(cam->horRange) * cam->focalLength;
		cam->xyTemplate[i].x = preRotX * cosOffset - cam->xyTemplate[i].y * sinOffset;	//rotation around cam
		cam->xyTemplate[i].y = preRotX * sinOffset + cam->xyTemplate[i].y * cosOffset;
		cam->xyTemplate[i].z = 0;
		cam->xyTemplate[i] = vec_norm(cam->xyTemplate[i]);
		cam->horRange -= cam->deltaHorAngle;
	}
}

int	dirVector_init(t_cam_rt *cam)
{
	double	verRange;

	cam->rays = malloc(sizeof(t_ray) * cam->pixels[0]);
	if (!cam->rays)
		return (0);
	cam->xyTemplate = malloc(sizeof(t_vec3) * cam->pixels[0]);
	if (!cam->xyTemplate)
		return (free(cam->rays), 0);
	cam->focalLength = 180.0 / cam->fov;
	cam->horRange = asin(sin(cam->fov / (2 * RADIAN)) / cam->focalLength );
	cam->focusDist = (cos(cam->horRange) * cam->focalLength) - (cos(cam->fov / (RADIAN * 2)));
	cam->deltaHorAngle = 2 * cam->horRange / cam->pixels[0];
	if (fabs(cam->orientation.x) < EPSILON)
		cam->orientation.x += 2 * EPSILON;
	createXYTemplate(cam);
	verRange = (90 / ((SCREEN_WIDTH / SCREEN_HEIGHT) * cam->focalLength)) / (RADIAN * 2);
	cam->height = tan(verRange);
	cam->deltaHeight = cam->height / (cam->pixels[1] / 2);
	cam->rotationM = calcRotationMatrix(vec_norm(vec3(cam->orientation.y, -1 * cam->orientation.x, 0)),
		atan(cam->orientation.z / sqrt((cam->orientation.x * cam->orientation.x) + (cam->orientation.y * cam->orientation.y))));
	return (1);
}

void	kill_cam(t_cam_rt	*cam)
{
	free(cam->rays);
	free(cam->xyTemplate);
	//free(cam);
}