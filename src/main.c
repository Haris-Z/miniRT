/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:01:00 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 20:07:41 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "rt.h"
#include "../includes/rt_error.h"
//#include "libft.h"

// int	main(int ac, char **av)
// {
// 	t_app	app;

// 	(void)ac;
// 	(void)av;
// 	if (rt_app_init(&app, 900, 600, "miniRT") != 0)
// 		return (1);
// 	return (rt_app_run(&app));
// }

#include <stdio.h>
int	main(int ac, char **av)
{
	(void)av;
	//t_app	app;

	/* check cmd line input mandatory */
	if (ac != 2)
		return (rt_error(E_USAGE, "test"));
	printf("hello\n");

	/* initalize scene configs for parsing */
	// scene_init(&app.scene);
	// printf("Initialized scene ..\n");


	// printf("Parsing %s ...\n");
	// if (parse_rt_file(av[1], &app.scene) != 0)
	// {
	// 	printf("Failed to parse %s ...\n");
	// 	return (RT_EXIT_FAILURE);
	// }
	/* add debug log printing scene file */
	//
	//

	/* initialize program */
	// if (rt_app_init(&app, SCREEN_WIDTH, SCREEN_HEIGHT, RT_WINDOW_NAME) != 0)
	// {
	// 	rt_error("Failed to initialize application.");
	// 	scene_clear(&app.scene);
	// 	return (RT_EXIT_FAILURE);
	// }
	//return (rt_app_run(&app));
	return (0);
}