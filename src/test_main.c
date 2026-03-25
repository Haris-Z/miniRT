/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:53 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 20:01:39 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "debug_print.h"
#include "parse.h"

// chang to 0 to not print scene_info
#ifndef DBG
# define DBG 1
#endif

// test_load_scene
int	main(int argc, char **argv)
{
	t_rt_file	f;
	t_scene		scene_info;
	t_rt_mlx	app;

	rt_load_file(argc, argv[1], &f);
	if (load_scene(f.fd, &scene_info) != 0)
		return (1);
	if (DBG)
	{
		print_scene_info(scene_info, argv[1]);
		//exit(1);
	}
	if (rt_init(&app, RT_WINDOW_NAME) != 0)
		return (1);
	if (render(&scene_info, &app))
		mlx_put_image_to_window(app.mlx, app.win, app.img.ptr, 0, 0);
	// save_to_ppm(argv[1], &app.img);
	printf("DONEEE");
	fflush(NULL);
	rt_run(&app);
	scene_clear(&scene_info);
	return (0);
}