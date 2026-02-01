/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:53 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 16:42:31 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mrt.h"
#include "rt_error.h"
#include "libft.h"

static void	print_scene_info(t_scene scene, char *file);

void	rotTest()
{
	t_vec3 a = vec3(0.7071,0.7071,0);
	// t_mat3 ones = matNew(vec3(1,1,1),vec3(1,1,1),vec3(1,1,1));
	// printV(vec_mul_M(a, ones));
	// t_mat3 i = matNew(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
	t_mat3 R = calcRotationMatrix(vec3(0,1,0), 90 / RADIAN);
	// t_vec3 axis = vec_norm(vec3(cam.orientation.y, -1 * cam.orientation.x, 0));

	a = vec_mul_M(a, R);
	printV(a);

}

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
	app.cam = cam_init(scene_info, SCREEN_WIDTH, SCREEN_HEIGHT);
	app.cam.items = &scene_info.objs;
	if (!dir_vector_init(&app.cam))
		return (0); // was a mallocerr
	int	i = -1;
	t_obj	*item;
	///start = timer()
	// rotTest(app.cam);
	while(++i < app.cam.pixels[1])
	{
		add_dir_vector_row(&app.cam);
		item = *app.cam.items;
		int j;
		while(item)
		{
			update_ray_dist(&app, item);
			item = item->next;
		}
		j = -1;
		while(++j < app.cam.pixels[0])
		{
			if (app.cam.rays[j].closestitem)
				app.img.addr[i * app.w +j] = color_to_mlx(compute_color(app,app.cam.rays[j], app.cam.items));
		}
	}/// end = timer(
	// printf(end-start);
	printf("DONE!!\n");
	fflush(NULL);
	mlx_put_image_to_window(app.mlx, app.win, app.img.ptr, 0, 0);
	// save_to_ppm(argv[1], &app.img);
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
			   scene.amb.ratio, scene.amb.color.x, scene.amb.color.y, scene.amb.color.z, scene.amb.rgb, scene.amb.rgb);
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
			printf("Sphere:     center(%.2f,%.2f,%.2f) | radius=%.2f | sp.color=(%f,%f,%f) |\n",
				   obj->sphere.center.x, obj->sphere.center.y, obj->sphere.center.z,
				   obj->sphere.radius, obj->sphere.color.x, obj->sphere.color.y, obj->sphere.color.z
				);
		else if (obj->type == OBJ_PLANE)
			printf("Plane:      point(%.2f,%.2f,%.2f) | normal(%.2f,%.2f,%.2f) | pl.color=(%f,%f,%f) |\n",
					obj->plane.point.x, obj->plane.point.y, obj->plane.point.z,
					obj->plane.normal.x, obj->plane.normal.y, obj->plane.normal.z, \
					obj->plane.color.x, obj->plane.color.y, obj->plane.color.z
				);
		else if (obj->type == OBJ_CYLINDER)
			printf("Cylinder:   center(%.2f,%.2f,%.2f) | axis=(%.2f,%.2f,%.2f) | diameter=%.2f | height=%.2f | cy.color=(%f,%f,%f) |\n",
				   obj->cylinder.center.x, obj->cylinder.center.y, obj->cylinder.center.z, \
				   obj->cylinder.axis.x, obj->cylinder.axis.y, obj->cylinder.axis.z, \
				   obj->cylinder.diameter, obj->cylinder.height, \
				obj->cylinder.color.x, obj->cylinder.color.y, obj->cylinder.color.z);
		i++;
		obj = obj->next;
	}
	printf("=============================================================\n");
	printf("Objects: %d\n", i);
	printf("=============================================================\n");
}
