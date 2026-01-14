/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:01:00 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/14 14:15:10 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "rt_error.h"
#include "trace_log.h"
#include "dbg_log.h"
#include "parser.h"
#include "scene.h"
#include "vec.h"
#include <stdio.h>
//#include <stdbool.h>

static int	test_all_rt(int argc, char **argv);
static int	test_rt_init(int argc, char **av);
static int	test_rt_simple_draw(int ac, char **av);
static void	rt_draw_test_pattern(t_rt_mlx *rt);
static int	test_file_parsing(int argc, char **argv);
static int	test_scene_initializaton(int argc, char **argv);
static int	test_default_scene(void);
static int	test_default_render_sphere(void);
static int	test_default_render_scene_objs(void);
static void	print_scene_info(t_scene scene);

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	//test_default_scene();
	//test_file_parsing(argc, argv);
	//test_default_render_sphere();
	//test_default_render_scene_objs();
	
	return (0);
}

static int	test_default_render_scene_objs(void)
{
	t_rt_mlx	app;

	rt_log_set_level(LOG_NONE);
	ft_bzero(&app, sizeof(app));
	set_default_scene_sphere(&app.scene);
	if (rt_init(&app, 1920, 1080, RT_WINDOW_NAME) != 0)
		return (1);
	TRACELOG(LOG_DEBUG, "\nbpp=(%d) | endian=(%d) | line_len=(%d)", \
		app.img.bpp, \
		app.img.endian, \
		app.img.line_len);
	rt_render_default_objs(&app);
	rt_run(&app);
	rt_destroy(&app);
	return (0);
}

static int	test_default_render_sphere(void)
{
	t_rt_mlx	app;

	rt_log_set_level(LOG_DEBUG);
	ft_bzero(&app, sizeof(app));
	set_default_scene_sphere(&app.scene);
	if (rt_init(&app, 800, 600, RT_WINDOW_NAME) != 0)
		return (1);
	TRACELOG(LOG_DEBUG, "\nbpp=(%d) | endian=(%d) | line_len=(%d)", \
		app.img.bpp, \
		app.img.endian, \
		app.img.line_len);
	rt_render_default_sphere(&app);
	rt_run(&app);
	rt_destroy(&app);
	return (0);
}


static int	test_default_scene(void)
{
	t_rt_mlx	app;

	// (void)argc;
	// (void)argv;
	
	ft_bzero(&app, sizeof(app));
	set_default_scene_sphere(&app.scene);
	
	print_scene_info(app.scene);
	scene_clear(&app.scene);
	return (0);
}

// printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);
static int	test_scene_initializaton(int argc, char **argv)
{
	
	// A 0.2 255,255,255
	// C -50,1,20 0,0,1 70
	// L -40,0,30 0.7 255,255,255
	// sp 0,0,20.6 12.6 10,0,255
	//test_file_parsing(argc, argv);
	rt_log_set_level(LOG_DEBUG);
	(void)argc;
	(void)argv;
	t_rt_mlx	app = {0};
	t_camera	cam = {0};
	t_ambient	amb = {0};
	t_sphere	sp = {0};
	
	cam.pos = vec3(-50, 1, 20);
	cam.dir = vec_norm(vec3(0.0,0.0,1.0));
	cam.fov_deg = 70.0;

	amb.ratio = 0.2;
    amb.color = color_rgb(255, 255, 255);

	sp.center = vec3(0, 0, 20);
	sp.diameter = 12.6;
	sp.radius = sp.diameter * 0.5;
	sp.color = color_rgb(10, 0, 255);

	//t_sphere sphere[] = {sp};
	//int sp_count = 1;
	TRACELOG(LOG_TRACE,"Settings from mini.rt file:\n");
	TRACELOG(LOG_INFO,"cam.pos.x=%f cam.pos.y=%f cam.pos.z=%f\n", cam.pos.x, cam.pos.y, cam.pos.z);
	TRACELOG(LOG_INFO,"cam.dir.x=%f cam.dir.y=%f cam.dir.z=%f\n", cam.dir.x, cam.dir.y, cam.dir.z);
	TRACELOG(LOG_INFO,"amb.ratio: %f\n", amb.ratio);
	TRACELOG(LOG_INFO,"amb.color.x=%f amb.color.y=%f amb.color.z=%f\n", amb.color.x, amb.color.y, amb.color.z);
	TRACELOG(LOG_INFO,"sp.center: (%.1f, %.1f, %.1f), sp.radius: %.1f\n", sp.center.x, sp.center.y, sp.center.z, sp.radius);
	//TRACELOG(LOG_INFO,"sp->center: (%.1f, %.1f, %.1f), sphere->radius: %.1f sphere->radius: %.1f\n , count: %d", sphere->center.x, sphere->center.y, sphere->center.z, sphere->radius, sphere->diameter, sp_count);
	
	scene_init(&app.scene);
	return (0);
}
static int	test_file_parsing(int argc, char **argv)
{
	t_rt_mlx	app;
	//int			err;

	rt_log_set_level(LOG_ALL);
	TRACELOG(LOG_INFO, "\n----------------\nFILE PARSER TEST\n----------------");
	if (argc != 2)
		rt_error_msg(MSG_USAGE);//rt_log_error(E_USAGE, NULL, -1, NULL);
	ft_bzero(&app, sizeof(app));
	//scene_init(&app.scene);
	TRACELOG(LOG_TRACE, "\nParsing file ->-> | %s |", argv[1]);
	if(parse_file(argv[1], &app.scene) != 0)
		return (1);
	TRACELOG(LOG_INFO, "\n(A) color=%.2f | ratio=%.2f\n", app.scene.amb.color, app.scene.amb.ratio);
	TRACELOG(LOG_INFO, "\n(C) (vp direction ) pos.x=%.2f | pos.y=%.2f | pos.z=%.2f \n\
(C) (orientation  ) dir.x=%.2f | dir.y=%.2f | dir.z=%.2f\n\
(C) (fov in deg)   fov_deg = %.2f\n",
	app.scene.cam.pos.x, app.scene.cam.pos.y, app.scene.cam.pos.z,
	app.scene.cam.dir.x, app.scene.cam.dir.y, app.scene.cam.dir.z,
	app.scene.cam.fov_deg );
	TRACELOG(LOG_INFO, "\n(L) (position)     pos.x=%.2f | pos.y=%.2f | pos.z=%.2f\n\
(L) (brightness )  %.2f\n\
(L) (color )       pos.x=%.2f | pos.y=%.2f | pos.z=%.2f\n",
	app.scene.light.pos.x, app.scene.light.pos.y, app.scene.light.pos.z,
	app.scene.light.bright,
	app.scene.light.color.x, app.scene.light.color.y, app.scene.light.color.z);

	TRACELOG(LOG_INFO, "\n(sp)  pos.x=%.2f | pos.y=%.2f | pos.z=%.2f\n", app.scene.objs->u.sp.center.x, app.scene.objs->u.sp.center.y, app.scene.objs->u.sp.center.z);

	scene_clear(&app.scene);
	// id	center	diameter		color
	// sp	0,0,20				20		255,0,0
	return (0);
}


static int	test_all_rt(int argc, char **argv)
{
	test_rt_simple_draw(argc, argv);
	return (0);
	//return (rt_run(&app));
}

static int	test_rt_init(int argc, char **argv)
{
	t_rt_mlx	app;
	// t_eflag		err;

	(void)argc;
	(void)argv;
	ft_bzero(&app, sizeof(app));
	TRACELOG(LOG_INFO, "Initializing rt ...");
	// err = 
	if (rt_init(&app, 900, 600, RT_WINDOW_NAME) != 0)
	{
		rt_error_log(E_RT_MLX_INIT, NULL, 0, NULL);
		return (1); // err
	}
	TRACELOG(LOG_INFO, "Running miniRT ...");
	rt_run(&app);
	rt_draw_test_pattern(&app);
	rt_destroy(&app);
	return (0);
	/* valgrind output 
	==41200== HEAP SUMMARY:
	==41200==     in use at exit: 0 bytes in 0 blocks
	==41200==   total heap usage: 25,213 allocs, 25,213 frees, 675,016 bytes allocated
	*/
	
	//return (rt_run(&app));
}

static int	test_rt_simple_draw(int argc, char **argv)
{
	t_rt_mlx	app;
	// t_eflag		err;
	rt_log_set_level(LOG_ALL);

	(void)argc;
	(void)argv;
	ft_bzero(&app, sizeof(app));
	TRACELOG(LOG_INFO, "Initializing rt ...");
	// err = 
	if (rt_init(&app, 900, 800, RT_WINDOW_NAME) != 0)
	{
		rt_error_log(E_RT_MLX_INIT, NULL, 0, NULL);
		return (1); // err
	}
	TRACELOG(LOG_INFO, "Running miniRT ...");
	TRACELOG(LOG_INFO, "app{.h=%d .w=%d, img.line_len=%d}", app.h, app.w, app.img.line_len);
	debug_log("t_rt_mlx -> sizeof app=%zu\n",sizeof(app));
	rt_draw_test_pattern(&app);
	rt_run(&app);
	rt_destroy(&app); //
	TRACELOG(LOG_TRACE, "Done miniRT ...");
	return (0);
	/* valgrind output 
	==75732== HEAP SUMMARY:
	==75732==     in use at exit: 0 bytes in 0 blocks
	==75732==   total heap usage: 17,179 allocs, 17,179 frees, 482,952 bytes allocated
	*/
	//return (rt_run(&app));
}

static void	rt_draw_test_pattern(t_rt_mlx *rt)
{
	int	x;
	int	y;

	y = 0;
	while (y < rt->img.img_h)
	{
		x = 0;
		while (x < rt->img.img_w)
		{
			if (x == y || x == rt->img.img_w - y - 1)
				rt_img_put_pixel(&rt->img, x, y, mlx_get_color_value(rt->mlx, 0x00FFAAAA)); //rt_img_put_pixel(&rt->img, x, y, 0x00FFAA00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.ptr, 0, 0);
}

// int	main(int argc, char **argv)
// {
// 	t_rt_mlx	app;

// 	(void)argc;
// 	(void)argv;
// 	ft_bzero(&app, sizeof(app));
// 	TRACELOG(LOG_INFO, "Initializing rt ...");
// 	if (rt_init(&app, 900, 600, RT_WINDOW_NAME) != 0)
// 	{
// 		rt_log_error(E_RT_MLX_INIT, NULL, 0, NULL);
// 		return (1);
// 	}
// 	TRACELOG(LOG_INFO, "Running miniRT ...");
// 	rt_run(&app);
// 	rt_destroy(&app);
// 	return (0);
// 	//return (rt_run(&app));
// }

static void	print_scene_info(t_scene scene)
{
	printf("======================  PARSED SCENE  ======================\n");
	if (scene.has_ambient)
		printf("Ambient: ratio=%.2f color=(%f,%f,%f)\n",
			   scene.amb.ratio, scene.amb.color.x, scene.amb.color.x, scene.amb.color.z);
	if (scene.has_camera)
		printf("Camera:  pos(%.2f,%.2f,%.2f) dir(%.2f,%.2f,%.2f) fov=%.1f°\n",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z,
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z,
			   scene.cam.fov_deg);
	if (scene.has_light)
		printf("Light:   pos(%.2f,%.2f,%.2f) brightness=%.2f\n \
			 color=(%f,%f,%f)\n",
			   scene.light.pos.x, scene.light.pos.y, scene.light.pos.z,
			   scene.light.bright, scene.light.color.x, scene.light.color.y, scene.light.color.z);
	printf("Objects: %d\n", scene.obj_count);
	t_obj *obj = scene.objs;
	while (obj)
	{
		printf("  - ");
		if (obj->type == OBJ_SPHERE)
			printf("Sphere:     center(%.2f,%.2f,%.2f) radius=%.2f\n",
				   obj->u.sp.center.x, obj->u.sp.center.y, obj->u.sp.center.z,
				   obj->u.sp.radius);
		else if (obj->type == OBJ_PLANE)
			printf("Plane:      point(%.2f,%.2f,%.2f) normal(%.2f,%.2f,%.2f)\n",
				   obj->u.pl.point.x, obj->u.pl.point.y, obj->u.pl.point.z,
				   obj->u.pl.normal.x, obj->u.pl.normal.y, obj->u.pl.normal.z);
		else if (obj->type == OBJ_CYLINDER)
			printf("Cylinder:   center(%.2f,%.2f,%.2f) radius=%.2f height=%.2f\n",
				   obj->u.cy.center.x, obj->u.cy.center.y, obj->u.cy.center.z,
				   obj->u.cy.radius, obj->u.cy.height);
		obj = obj->next;
	}
	printf("=============================================================\n");
}