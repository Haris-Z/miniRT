/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:01:00 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 19:52:41 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "rt_error.h"
#include "trace_log.h"
#include "dbg_log.h"
#include <stdio.h>
//#include <stdbool.h>

static int	test_rt_init(int ac, char **av);
static int	test_rt_simple_draw(int ac, char **av);
static void	rt_draw_test_pattern(t_rt_mlx *rt);

// printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);

int	main(int argc, char **argv)
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

// int	main(int ac, char **av)
// {
// 	t_rt_mlx	app;

// 	(void)ac;
// 	(void)av;
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