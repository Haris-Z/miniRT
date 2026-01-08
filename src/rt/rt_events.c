/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:04:18 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 18:45:02 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// window management

// ends the window loop
static int	rt_request_quit(t_rt_mlx *rt)
{
	rt->should_quit = 1;
	mlx_loop_end(rt->mlx);
	return (0);
}

// runs on any keypress - if ESC is pressed closes window
int	rt_on_keypress(int keycode, void *param)
{
	t_rt_mlx	*rt;

	rt = (t_rt_mlx *)param;
	if (keycode == XK_Escape)
		return (rt_request_quit(rt));
	// #include <stdio.h>
	// printf("%d\n", keycode);
	return (0);
}
// runs when window closed with x button
int	rt_on_destroy(void *param)
{
	t_rt_mlx	*rt;

	rt = (t_rt_mlx *)param;
	return (rt_request_quit(rt));
}
// triggered when window needs to redraw -> 
// covered, resized focus change etc
int	rt_on_expose(void *param)
{
	t_rt_mlx	*rt;

	rt = (t_rt_mlx *)param;
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.ptr, 0, 0);
	return (0);
}

// placeholder for later if/when adding on top of rendered image
// or rerendering on keypresses
// does nothing for now
int	rt_on_loop(void *param)
{
	(void)param;
	return (0);
}