/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:01:00 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/10 09:51:14 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "rt_error.h"
#include "trace_log.h"
#include "dbg_log.h"
#include "parser.h"
#include "scene.h"
#include <stdio.h>
//#include <stdbool.h>

static int	test_all_rt(int argc, char **argv);
static int	test_rt_init(int argc, char **av);
static int	test_rt_simple_draw(int ac, char **av);
static void	rt_draw_test_pattern(t_rt_mlx *rt);

// printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);

int	main(int argc, char **argv)
{
	t_rt_mlx	app;
	//int			err;

	rt_log_set_level(LOG_ALL);
	if (argc != 2)
		rt_log_error(E_USAGE, NULL, -1, NULL);
	ft_bzero(&app, sizeof(app));
	TRACELOG(LOG_INFO, "\nParsing file %s ", argv[1]);
	if(parse_file(argv[1], &app.scene) != 0)
		return (1);
	TRACELOG(LOG_INFO, "\n(A) color=%.2f | ratio=%.2f\n", app.scene.amb.color, app.scene.amb.ratio);
	TRACELOG(LOG_INFO, "\n(C) (vp direction ) pos.x=%.2f | pos.y=%.2f | pos.z=%.2f \n\
(C) (orientation  ) dir.x=%.2f | dir.y=%.2f | dir.z=%.2f\n\
(C) (fov in deg)   fov_deg = %.2f\n",
	app.scene.cam.pos.x, app.scene.cam.pos.y, app.scene.cam.pos.z,
	app.scene.cam.dir.x, app.scene.cam.dir.z, app.scene.cam.dir.z,
	app.scene.cam.fov_deg );
	TRACELOG(LOG_INFO, "\n(L)  pos.x=%.2f | pos.y=%.2f | pos.z=%.2f\n\
(L) (brightness ) %.2f\n\
(L) (color )   pos.x=%.2f | pos.y=%.2f | pos.z=%.2f\n",
	app.scene.light.pos.x, app.scene.light.pos.y, app.scene.light.pos.z,
	app.scene.light.bright,
	app.scene.light.color.x, app.scene.light.color.y, app.scene.light.color.z);

	TRACELOG(LOG_INFO, "\n(sp)  pos.x=%.2f | pos.y=%.2f | pos.z=%.2f\n", app.scene.objs->u.sp.center.x, app.scene.objs->u.sp.center.y, app.scene.objs->u.sp.center.z);

	scene_clear(&app.scene);
	// id	center	diameter/radius		color
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
		rt_log_error(E_RT_MLX_INIT, NULL, 0, NULL);
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
		rt_log_error(E_RT_MLX_INIT, NULL, 0, NULL);
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