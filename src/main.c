#include "../includes/mini.h"

int	close_game(t_vars *vars)
{
	kill_cam(vars->cam);
	mlx_destroy_image(vars->mlx, vars->colors->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->colors);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_game(vars);
	return (0);
}

static t_data	*init_data(t_vars *vars, int screendim[2])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	
	data->img = mlx_new_image(vars->mlx, screendim[0], screendim[1]);
	data->bits_per_pixel = 32;
	data->line_length = screendim[0];
	data->endian = 1;
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
							&data->endian);	
	if (!(data->img))
		return (free(data), NULL);
	return (data);
}

int	init_vars(t_vars *vars, int screendim[2])
{
	vars->mlx = NULL;
	vars->mlx = mlx_init();
	vars->ambient = 0.1;
	if (!(vars->mlx))
		return (0);
	vars->win = mlx_new_window(vars->mlx, screendim[0], screendim[1], "Trace my rays!");
	if (!(vars->win))
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		return (0);
	}
	return (1);
}

int main()
{
	vector**	colors;
	int			fov = 120;
	vector		campos;
	vector		camdir;
	campos.x = -5;
	campos.y = 0;
	campos.z = 8;
	camdir.x = 1;
	camdir.y = 0;
	camdir.z = -0.1;
	camdir = normalizev(camdir);

	int	screendim[2] = {1400,800};

	t_item	*items;
	t_item	plane;

	plane.t_type = PLANE;
	plane.plane.point.x = 0;
	plane.plane.point.y = 0;
	plane.plane.point.z = 0;
	plane.plane.orientation.x = 0;
	plane.plane.orientation.y = 0;
	plane.plane.orientation.z = 1;
	plane.plane.orientation = normalizev(plane.plane.orientation);
	plane.color = 0x003030A0;

	t_item	plane2;

	plane2.t_type = PLANE;
	plane2.plane.point.x = 0;
	plane2.plane.point.y = 1;
	plane2.plane.point.z = 0;
	plane2.plane.orientation.x = 0;
	plane2.plane.orientation.y = 1;
	plane2.plane.orientation.z = 1;
	plane2.plane.orientation = normalizev(plane2.plane.orientation);
	plane2.color = 0x00A0AAAA;
	
	t_item	ball;

	ball.t_type = SHPERE;
	ball.sphere.pos.x = 9;
	ball.sphere.pos.y = 1;
	ball.sphere.pos.z = 3;
	ball.sphere.radius = 2;
	ball.color = 0x0072903F;

	t_item	ball2;

	ball2.t_type = SHPERE;
	ball2.sphere.pos.x = 8;
	ball2.sphere.pos.y = 1;
	ball2.sphere.pos.z = 6.5;
	ball2.sphere.radius = 1;
	ball2.color = 0x0020A020;

	items = &plane;
	// plane.next = &plane2;
	plane.next = &ball;
	// plane2.next = &ball;
	ball.next = &ball2;
	ball2.next = NULL;

	vector light;
	light.x = 9;
	light.y = 1;
	light.z = 100;
	
	t_vars	vars;
	init_vars(&vars, screendim);
	vars.cam = cam_init(campos, camdir, fov, screendim);
	dirVector_init(vars.cam);
	vars.colors = init_data(&vars, screendim);
	t_rays	*rays;
	rays = malloc(sizeof(t_rays) * screendim[0]);
	int	i = -1;
	while(++i < screendim[1])
	{
		int j = -1;
		while(++j < screendim[0])
		{
			(rays+j)->dist = -1.0;
			(rays+j)->closestitem = NULL;
		}
		updateRayDist(screendim[0], i, &vars, &ball, rays);
		updateRayDist(screendim[0], i, &vars, &ball2, rays);
		updateRayDist(screendim[0], i, &vars, &plane, rays);
		// updateRayDist(screendim[0], i, &vars, &plane2, rays);
		j = -1;
		while(++j < screendim[0])
		{
			if (rays[j].closestitem)
			{
				int ambientColor = scaleColor(0, rays[j].closestitem->color, vars.ambient);
				double lightAngle = getLightAngle(campos, vars.cam->dirvectors[i][j] ,rays[j], light, items);
				// vars.colors->addr[i*screendim[0]+j] = computeColor(vars, rays[j], items);
				if (lightAngle > 0)
				{
					vars.colors->addr[i*screendim[0]+j] = scaleColor(ambientColor, rays[j].closestitem->color, lightAngle);
				}
				else
					vars.colors->addr[i*screendim[0]+j] = ambientColor;
			}
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.colors->img, 0, 0);

	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, &close_game, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
