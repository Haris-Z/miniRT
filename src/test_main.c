/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:53 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/08 14:35:07 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mrt.h"
#include "debug_print.h"

#include "rt_error.h"
#include "libft.h"

/*
**  ###############################
**	MAIN WITH LIST-TO-ARRAY
**  ###############################
*/

int	main(int argc, char **argv)
{
	t_rt_mlx	app;
	t_scene		scene_info;
	// t_obj		*objs;
	int			objs_n;
	
	// check args
	ft_bzero(&app, sizeof(app));
	if (argc != 2)
		return(rt_error_msg(MSG_USAGE));
		
	// init scene parse file
	ft_bzero(&scene_info, sizeof(scene_info));
	if(parse_file(argv[1], &scene_info) != 0)
		return (1);
	
	// list to array
	if (scene_obj_array(&scene_info) != 0)
		return (1);


	// CHECK 
	// int t = 0;
	// objs = scene_info.objs_arr;
	objs_n = scene_info.objs_n;
	
	// init mlx stuff
	if (rt_init(&app, RT_WINDOW_NAME) != 0)
		return (1);

	// init render stuff
	app.cam = cam_init(scene_info, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!dir_vector_init(&app.cam))
		return (rt_error_msg("malloc\n")); // was a mallocerr
	app.cam.items = &scene_info.objs_arr;
	(*app.cam.items)->obj_total = objs_n;

	render(scene_info, app);
	printf("DONE!!\n");
	fflush(NULL);
	mlx_put_image_to_window(app.mlx, app.win, app.img.ptr, 0, 0);
	save_to_ppm(argv[1], &app.img);
	rt_run(&app);
	rt_destroy(&app);
	scene_clear(&scene_info);
	return (0);
}

/*
**  ###############################
**	PREVIOUS MAIN WITH LIST
**  ###############################
*/

// int	main(int argc, char **argv)
// {
// 	t_rt_mlx	app;
// 	t_scene		scene_info;

// 	// check args
// 	ft_bzero(&app, sizeof(app));
// 	if (argc != 2)
// 		return(rt_error_msg(MSG_USAGE));
// 	// init scene parse file
// 	ft_bzero(&scene_info, sizeof(scene_info));
// 	if(parse_file(argv[1], &scene_info) != 0)
// 		return (1);
// 	print_scene_info(scene_info, argv[1]);

	
// 	if (rt_init(&app, RT_WINDOW_NAME) != 0)
// 		return (1);
// 	app.cam = cam_init(scene_info, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	app.cam.items = &scene_info.objs;
// 	if (!dir_vector_init(&app.cam))
// 		return (0); // was a mallocerr
// 	int	i = -1;
// 	t_obj	*item;
// 	///start = timer()
// 	// rotTest(app.cam);
// 	while(++i < app.cam.pixels[1])
// 	{
// 		add_dir_vector_row(&app.cam);
// 		item = *app.cam.items;
// 		int j;
// 		while(item)
// 		{
// 			update_ray_dist(&app, item);
// 			item = item->next;
// 		}
// 		j = -1;
// 		while(++j < app.cam.pixels[0])
// 		{
// 			if (app.cam.rays[j].closestitem)
// 				app.img.addr[i * app.w +j] = color_to_mlx(compute_color(app,app.cam.rays[j], app.cam.items));
// 		}
// 	}/// end = timer(
// 	// printf(end-start);
// 	printf("DONE!!\n");
// 	fflush(NULL);
// 	mlx_put_image_to_window(app.mlx, app.win, app.img.ptr, 0, 0);
// 	// save_to_ppm(argv[1], &app.img);
// 	rt_run(&app);
// 	rt_destroy(&app);
// 	scene_clear(&scene_info);
// 	return (0);
// }
