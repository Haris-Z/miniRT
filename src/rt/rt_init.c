/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:29:17 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 16:24:57 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"

// static void	clamp_to_screen(void *mlx, int *w, int *h)
// {
// 	int	sw;
// 	int	sh;
// 
// 	if (mlx_get_screen_size(mlx, &sw, &sh) == 0)
// 	{
// 		if (*w > sw)
// 			*w = sw;
// 		if (*h > sh)
// 			*h = sh;
// 	}
// }

int	rt_init(t_rt_mlx *rt, const char *title)
{
	int	w;
	int	h;

	w = SCREEN_WIDTH;
	h = SCREEN_HEIGHT;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (1);
	rt->win = mlx_new_window(rt->mlx, w, h, (char *)title);
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
