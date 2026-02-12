/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:29:17 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/06 16:31:52 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"


static void clamp_to_screen(void *mlx, int *w, int *h)
{
	int	sw;
	int	sh;

	if (mlx_get_screen_size(mlx, &sw, &sh) == 0)
	{
		if (*w > sw)
			*w = sw;
		if (*h > sh)
			*h = sh;
	}
}

int rt_init(t_rt_mlx *rt, const char *title)
{
	int	w;
	int	h;

	w = SCREEN_WIDTH;
	h = SCREEN_HEIGHT;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (1);
	// clamp_to_screen(rt->mlx, &w, &h);
	rt->win = mlx_new_window(rt->mlx, w, h , (char *)title);
	if (!rt->win)
	{
		rt_destroy(rt);
		return (1);
	}
	if (rt_img_create(rt, &rt->img, w, h) != 0)
	{
		rt_destroy(rt);
		return (1);
	}
	rt->h = h;
	rt->w = w;
	return (0);
}

/* 
** Description 
*/
// #include <stdio.h>
// int	rt_init(t_rt_mlx *rt, int w, int h, const char *title)
// {
// 	rt->mlx = mlx_init();
// 	if (!rt->mlx)
// 		return (1);
// 	// mlx_get_screen_size(rt->mlx, &rt->w, &rt->h);
// 	// if (w >= rt->w)
// 	// 	w = rt->w;
// 	// if (h >= rt->h)
// 	// 	w = rt->h;
// 	// printf("rt->w %d | rt->h %d\n", rt->w, rt->h);
// 	rt->win = mlx_new_window(rt->mlx, w, h, (char *)title);
// 	if (!rt->win)
// 	{
// 		rt_destroy(rt);
// 		return (1);
// 	}
// 	if (rt_img_create(rt, &rt->img, w, h) != 0)
// 	{
// 		rt_destroy(rt);
// 		return (1);
// 	}
// 	return (0);
// }

/* 
** Description 
*/
void	rt_destroy(t_rt_mlx *rt)
{
	if (rt->cam.rays)
		free(rt->cam.rays);
	if (rt->img.ptr)
		rt_img_destroy(rt, &rt->img);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img.ptr = NULL;
}