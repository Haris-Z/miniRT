#include "../includes/mini.h"

t_camera	*cam_init(vector pos, vector orientation, int fov, int screendim[2])
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->orientation = orientation;
	cam->pixels[0] = screendim[0];
	cam->pixels[1] = screendim[1];
	cam->pos = pos;
	cam->fov = fov;
	return (cam);
}

void	addDirVectorRow(vector row[], t_camera *cam, double rangeA, double horOffset, double deltaA, double verOffset)
{
	int	i;

	i = -1;
	while(++i < cam->pixels[0])
	{
		row[i].x = cos(horOffset + rangeA) * sin((90.0/57.2958) - verOffset);
		row[i].y = sin(horOffset + rangeA) * sin((90.0/57.2958) - verOffset);
		row[i].z = cos((90.0/57.2958) - verOffset);
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

	deltaA = cam->fov / 57.2958;
	double	rangeA = deltaA / 2;
	printf("range %f\n",rangeA);
	deltaA /= cam->pixels[0];
	printf("delta A %f\n",deltaA);

	horOffset = atan(cam->orientation.y / cam->orientation.x);
	printf("hoffset %f\n", (horOffset * 57.2958));

	deltaB = 90 / 57.2958;
	double	rangeB = deltaB / 2;
	deltaB /= cam->pixels[1];

	verOffset = sqrt(cam->orientation.x * cam->orientation.x + cam->orientation.y * cam->orientation.y);
	verOffset = atan(cam->orientation.z / verOffset);
	printf("verOffset %f\n", (verOffset * 57.2958));

	cam->dirvectors = malloc(sizeof(vector*) * cam->pixels[1]);
	i = -1;
	while (++i < cam->pixels[1])
	{
		cam->dirvectors[i] = malloc(sizeof(vector) * cam->pixels[0]);
		addDirVectorRow(cam->dirvectors[i], cam, rangeA, horOffset, deltaA, verOffset + rangeB);
		rangeB -= deltaB;
	}
	return 1;
}