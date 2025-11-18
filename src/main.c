#include "../includes/mini.h"

int	close_game(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->colors->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
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
	data->line_length = 1000;
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
	if (!(vars->mlx))
		return (0);
	
	vars->win = mlx_new_window(vars->mlx, screendim[0], screendim[1], "Hello world!");
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
	campos.x = 0;
	campos.y = 0;
	campos.z = 0;
	camdir.x = 1;
	camdir.y = 0;
	camdir.z = 0;

	int	screendim[2] = {1400,800};

	t_camera	*cam;
	cam = cam_init(campos, camdir, fov, screendim);
	dirVector_init(cam);

	t_item	ball;

	ball.pos.x = 1;
	ball.pos.y = 0.5;
	ball.pos.z = 0;
	ball.radius = 0.8;

	t_vars	vars;
	init_vars(&vars, screendim);
	vars.colors = init_data(&vars, screendim);
	double dist;
	int i = -1;
	while(++i < screendim[1])
	{
		int j = -1;
		while(++j < screendim[0])
		{
			dist = hitSp(cam->dirvectors[i][j], ball);
			if (dist != -1.0)
			{
				vars.colors->addr[i*screendim[0]+j] =  ((int)(dist * 256 ));
				// printf("dist: %f\n",(0x00FF0000 + (dist -1) * 255.9999));
			}
		}
	}
		mlx_put_image_to_window(vars.mlx, vars.win, vars.colors->img, 0, 0);

	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, &close_game, &vars);
	mlx_loop(vars.mlx);

	free(colors);

	return (0);
}