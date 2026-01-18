/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:01:00 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/18 08:55:05 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt_error.h"
#include "parser.h"
#include "rt.h"
#include "libft.h"

static int	test_rt_init(int argc, char **av);
static int	test_file_parsing(int argc, char **argv);
static void	rt_draw_test_pattern(t_rt_mlx *rt);
static void	print_scene_info(t_scene scene, char *file);

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	test_rt_init(argc, argv);
	sleep(2);
	test_file_parsing(argc, argv);
	return (0);
}

static int	test_rt_init(int argc, char **argv)
{
	t_rt_mlx	app;

	(void)argc;
	(void)argv;
	ft_bzero(&app, sizeof(app));
	if (rt_init(&app, RT_WINDOW_NAME) != 0)
		return (1);
	rt_draw_test_pattern(&app);
	rt_run(&app);
	rt_destroy(&app);
	return (0);
}

static int	test_file_parsing(int argc, char **argv)
{
	t_scene		scene_info;

	if (argc != 2)
		return(rt_error_msg(MSG_USAGE));
	ft_bzero(&scene_info, sizeof(scene_info));
	if(parse_file(argv[1], &scene_info) != 0)
		return (1);
	print_scene_info(scene_info, argv[1]);
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
		else if (obj->type == OBJ_SPHERE)
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