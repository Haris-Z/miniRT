#include "mini.h"
#include "rt_error.h"
#include "cam.h"
#include "parser.h"
#include "rt.h"
#include "scene.h"
#include "vec.h"
#include "libft.h"
#include <stdio.h>

static void	print_scene_info(t_scene scene, char *file);

// int	close_game(t_rt_mlx *vars)
// {
	//kill_cam(&vars->cam);
	// mlx_destroy_image(vars->mlx, vars->colors->img);
	// mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	// free(vars->mlx);
	// free(vars->colors);
	// exit(0);
// 	return (0);
// }

// static t_rt_img	*init_data(t_rt_mlx *vars, int screendim[2])
// {
// 	t_rt_img	*data;

// 	data = malloc(sizeof(t_rt_img));
// 	if (!data)
// 		return (NULL);
	
// 	data->img = mlx_new_image(vars->mlx, screendim[0], screendim[1]);
// 	data->bits_per_pixel = 32;
// 	data->line_length = screendim[0];
// 	data->endian = 1;
// 	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
// 							&data->endian);	
// 	if (!(data->img))
// 		return (free(data), NULL);
// 	return (data);
// }

// int	init_vars(t_vars *vars, int screendim[2])
// {
// 	vars->mlx = NULL;
// 	vars->mlx = mlx_init();
// 	if (!(vars->mlx))
// 		return (0);
// 	vars->win = mlx_new_window(vars->mlx, screendim[0], screendim[1], "Trace my rays!");
// 	if (!(vars->win))
// 	{
// 		mlx_destroy_display(vars->mlx);
// 		free(vars->mlx);
// 		return (0);
// 	}
// 	return (1);
// }

// static int	test_rt_init(int argc, char **argv)
// {
// 	t_rt_mlx	app;

// 	(void)argc;
// 	(void)argv;
// 	ft_bzero(&app, sizeof(app));
// 	if (rt_init(&app, RT_WINDOW_NAME) != 0)
// 		return (1);
// 	rt_run(&app);
// 	rt_destroy(&app);
// 	return (0);
// }

// static int	test_file_parsing(int argc, char **argv)
// {
// 	t_scene		scene_info;

// 	if (argc != 2)
// 		return(rt_error_msg(MSG_USAGE));
// 	ft_bzero(&scene_info, sizeof(scene_info));
// 	if(parse_file(argv[1], &scene_info) != 0)
// 		return (1);
// 	print_scene_info(scene_info, argv[1]);
// 	scene_clear(&scene_info);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_rt_mlx	app;
	t_scene		scene_info;

	ft_bzero(&app, sizeof(app));
	if (argc != 2)
		return(rt_error_msg(MSG_USAGE));
	ft_bzero(&scene_info, sizeof(scene_info));
	if(parse_file(argv[1], &scene_info) != 0)
		return (1);
	print_scene_info(scene_info, argv[1]);
	if (rt_init(&app, RT_WINDOW_NAME) != 0)
		return (1);
	app.cam = cam_init(scene_info, 800, 600);
	app.cam.items = &scene_info.objs;
	dirVector_init(&app.cam);
	int	i = -1;
	t_obj	*item;
	while(++i < app.cam.pixels[1])
	{
		item = *app.cam.items;
		int j;
		while(item)
		{
			updateRayDist(i, &app, item);
			item = item->next;
		}
		j = -1;
		while(++j < app.cam.pixels[0])
		{
			if (app.cam.rays[i][j].closestitem)
				app.img.addr[i * app.w +j] = computeColor(app,app.cam.rays[i][j], app.cam.items);
		}
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img.ptr, 0, 0);
	rt_run(&app);
	rt_destroy(&app);
	scene_clear(&scene_info);
	return (0);
}

static void	print_scene_info(t_scene scene, char *file)
{
	printf("=========================   PARSED SCENE (%s) ==========================================================================\n\n", ft_strrchr(file, '/') + 1);
	
	printf("=========================  ELEMENTS  ==========================================================================\n\n");
	if (scene.has_ambient)
		printf("Ambient: ratio=%.2f			| color=(r=%f,g=%f,b=%f)\n \
					| color=%d | colorhex=0x%X\n\n",
			   scene.amb.ratio, scene.amb.color.x, scene.amb.color.x, scene.amb.color.z, scene.amb.rgb, scene.amb.rgb);
	if (scene.has_camera)
		printf("Camera:	 pos(x=%.2f,y=%.2f,z=%.2f)	| dir(x=%.2f,y=%.2f,z=%.2f)	| fov=%.1f°\n\n",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z,
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z,
			   scene.cam.fov_deg);
	if (scene.has_light)
		printf("Light:	 pos(%.2f,%.2f,%.2f)		| brightness=%.2f		| color=(%f,%f,%f) \n\
									| color=%d | colorhex=0x%X\n",
			   scene.light.pos.x, scene.light.pos.y, scene.light.pos.z,
			   scene.light.bright, scene.light.color.x, scene.light.color.y, scene.light.color.z, scene.light.rgb, scene.light.rgb);
	printf("=========================  OBJECTS  ============================================================================\n\n");
	t_obj *obj = scene.objs;
	int i = 0;
	while (obj)
	{
		printf("  - ");
		if (obj->type == OBJ_SPHERE)
			printf("Sphere:     center(%.2f,%.2f,%.2f) | radius=%.2f | sp.color=(%f,%f,%f) | obj.color=%d | obj.color=0x%X |\n",
				   obj->sphere.center.x, obj->sphere.center.y, obj->sphere.center.z,
				   obj->sphere.radius, obj->sphere.color.x, obj->sphere.color.y, obj->sphere.color.z, \
				   obj->color, obj->color\
				);
		else if (obj->type == OBJ_PLANE)
			printf("Plane:      point(%.2f,%.2f,%.2f) | normal(%.2f,%.2f,%.2f) | pl.color=(%f,%f,%f) | obj.color=%d | obj.color=0x%X |\n",
				   obj->plane.point.x, obj->plane.point.y, obj->plane.point.z,
				   obj->plane.normal.x, obj->plane.normal.y, obj->plane.normal.z, \
				obj->plane.color.x, obj->plane.color.y, obj->plane.color.z, \
			obj->color, obj->color);
		else if (obj->type == OBJ_CYLINDER)
			printf("Cylinder:   center(%.2f,%.2f,%.2f) | axis=(%.2f,%.2f,%.2f) | diameter=%.2f | height=%.2f | cy.color=(%f,%f,%f) | obj.color=%d | obj.color=0x%X |\n",
				   obj->cylinder.center.x, obj->cylinder.center.y, obj->cylinder.center.z, \
				   obj->cylinder.axis.x, obj->cylinder.axis.y, obj->cylinder.axis.z, \
				   obj->cylinder.diameter, obj->cylinder.height, \
				obj->cylinder.color.x, obj->cylinder.color.y, obj->cylinder.color.z, obj->color, obj->color);
		i++;
		obj = obj->next;
	}
	printf("=============================================================\n");
	printf("Objects: %d\n", i);
	printf("=============================================================\n");
}

