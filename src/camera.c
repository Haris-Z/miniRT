#include "../includes/mini.h"

t_camera	*cam_init(vector pos, vector orientation, int fov, int screendim[2])
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->orientation = orientation;
	cam->pos = pos;
	cam->pixels[0] = screendim[0];
	cam->pixels[1] = screendim[1];
	cam->ambient = 0.1;
	cam->fov = fov;
	return (cam);
}


void	addDirVectorRow(t_ray row[], t_camera *cam, double rangeA, double horOffset, double deltaA, double verOffset)
{
	int	i;

	i = -1;
	while(++i < cam->pixels[0])
	{
		// cilyndical viewport
		// row[i].x = cos(horOffset + rangeA);
		// row[i].y = sin(horOffset + rangeA);
		// row[i].z = verOffset;
		// rangeA -= deltaA;
		
		// spherical viewport
		// row[i].x = cos(horOffset + rangeA) * sin((90.0/57.2958) - verOffset);
		// row[i].y = sin(horOffset + rangeA) * sin((90.0/57.2958) - verOffset);
		// row[i].z = cos((90.0/57.2958) - verOffset);
		// rangeA -= deltaA;

		//plain viewport
		row[i].direction.x = 1;
		row[i].direction.y = -1 * (rangeA + horOffset);
		row[i].direction.z = verOffset;
		row[i].direction = normalizev(row[i].direction);
		row[i].dist = -1.0;
		row[i].closestitem = NULL;
		rangeA -= deltaA;
	}
}

int	dirVector_init(t_camera *cam)
{
	int		i;

	double	deltaA;
	double	deltaB;
	double	horOffset;
	double	verOffset;

	deltaA = cam->fov / RADIAN;
	double	rangeA = deltaA / 2;
	printf("range %f\n",rangeA);
	deltaA /= cam->pixels[0];
	printf("delta A %f\n",deltaA);

	horOffset = atan(cam->orientation.y / cam->orientation.x);
	printf("hoffset %f\n", (horOffset * RADIAN));

	deltaB = 90 / RADIAN;
	double	rangeB = deltaB / 2;
	deltaB /= cam->pixels[1];

	verOffset = sqrt(cam->orientation.x * cam->orientation.x + cam->orientation.y * cam->orientation.y);
	verOffset = atan(cam->orientation.z / verOffset);
	printf("verOffset %f\n", (verOffset * RADIAN));

	cam->rays = malloc(sizeof(t_ray*) * cam->pixels[1]);
	i = -1;
	while (++i < cam->pixels[1])
	{
		cam->rays[i] = malloc(sizeof(t_ray) * cam->pixels[0]);
		addDirVectorRow(cam->rays[i], cam, rangeA, horOffset, deltaA, verOffset + rangeB);
		rangeB -= deltaB;
	}
	return 1;
}

void	kill_cam(t_camera	*cam)
{
	int	i;
	int j;
	i = -1;
	while (++i < cam->pixels[1])
	{
		free(cam->rays[i]);
	}
	free(cam->rays);
	free(cam);
}