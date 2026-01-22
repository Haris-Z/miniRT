#include "mini.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>
#include "scene.h"

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
	double	horAngle;

	horAngle = cam->horRange;
	i = -1;
	while(++i < cam->pixels[0])
	{
		cam->rays[i].direction.x = (cos(horAngle) * cam->focalLength) - cam->focusDist;
		cam->rays[i].direction.y = sin(horAngle) * cam->focalLength * -1;
		cam->rays[i].direction.z = cam->verOffset;
		cam->rays[i].dist = -1.0;
		cam->rays[i].closestitem = NULL;
		horAngle -= cam->deltaHorAngle;
		cam->rays[i].direction = vec_norm(cam->rays[i].direction);
	}
	cam->verOffset -= cam->deltaVerAngle;
}

int	dirVector_init(t_cam_rt *cam)
{
	cam->rays = malloc(sizeof(t_ray) * cam->pixels[0]);
	if (!cam->rays)
		return (0);
	cam->focalLength = 180.0 / cam->fov;
	cam->horRange = asin(sin(cam->fov / (2 * RADIAN)) / cam->focalLength );
	cam->focusDist = (cos(cam->horRange) * cam->focalLength) - (cos(cam->fov / (RADIAN * 2)));
	cam->deltaHorAngle = 2 * cam->horRange / cam->pixels[0];
	if (fabs(cam->orientation.x) < EPSILON)
		cam->orientation.x += 2 * EPSILON;
	cam->horRange -= atan(cam->orientation.y / cam->orientation.x);
	cam->verOffset = (90 / ((SCREEN_WIDTH / SCREEN_HEIGHT) * cam->focalLength)) / (RADIAN * 2);
	cam->deltaVerAngle = (2 * cam->verOffset / cam->pixels[1]);
	cam->verOffset += atan(cam->orientation.z / sqrt((cam->orientation.x * cam->orientation.x) + (cam->orientation.y * cam->orientation.y)));
	// printf(" focalLength %f focusdist %f horrange %f deltahorizontal %f verrange %f deltavertical %f\n", 
	// 	cam->focalLength,cam->focusDist, cam->horRange * RADIAN,  cam->deltaHorAngle * RADIAN,cam->verOffset * RADIAN, cam->deltaVerAngle * RADIAN);	
	return (1);
}

void	kill_cam(t_cam_rt	*cam)
{
	free(cam->rays);
	free(cam);
}