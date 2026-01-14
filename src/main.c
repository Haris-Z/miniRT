/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:01:00 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/14 14:12:53 by hazunic          ###   ########.fr       */
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

static int	test_minirt(int argc, char **argv);
static int	test_default_render_scene_objs(int argc, char **argv);
static void	print_scene_info(t_scene scene);

int	main(int argc, char **argv)
{

	rt_log_set_level(LOG_NONE);
	test_minirt(argc, argv);
	//test_default_render_scene_objs(argc, argv);
	return (0);
}

static int	test_minirt(int argc, char **argv)
{
	t_rt_mlx	app;

	if (argc != 2)
		rt_error_msg(MSG_USAGE);
	ft_bzero(&app, sizeof(app));
	if(parse_file(argv[1], &app.scene) != 0)
		return (1);
	print_scene_info(app.scene);
	if (rt_init(&app, 800, 600, RT_WINDOW_NAME) != 0)
		return (1);
	rt_render_default_objs(&app);
	rt_run(&app);
	rt_destroy(&app);
	return (0);
}

static int	test_default_render_scene_objs(int argc, char **argv)
{
	t_rt_mlx	app;

	(void)argc;
	(void)argv;
	rt_log_set_level(LOG_NONE);
	ft_bzero(&app, sizeof(app));
	set_default_scene_sphere(&app.scene);
	print_scene_info(app.scene);
	if (rt_init(&app, 800, 600, RT_WINDOW_NAME) != 0)
		return (1);
	rt_render_default_objs(&app);
	rt_run(&app);
	rt_destroy(&app);
	return (0);
}

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