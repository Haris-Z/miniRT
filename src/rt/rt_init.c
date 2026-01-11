/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:29:17 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/11 09:00:01 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// return bool or error for rt_log_error?
/* 
** Description 
*/
int	rt_init(t_rt_mlx *rt, int w, int h, const char *title)
{
	//ft_bzero()
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img.ptr = NULL;
	rt->img.addr = NULL;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (E_RT_MLX_INIT); // or rt_log_error(rt_strerror(E_RT_MLX_INIT))
	rt->w = w;
	rt->h = h;
	rt->should_quit = 0;
	rt->win = mlx_new_window(rt->mlx, w, h, (char *)title);
	if (!rt->win)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
		return (E_RT_WIN_CREATE);
	}
	if (rt_img_create(rt, &rt->img, w, h) != 0)
	{
		rt_destroy(rt);
		return (E_RT_IMG_CREATE);
	}
	return (0); // E_OK
}

// check if all alloacted is here
// [ ] add scene_clear( ) later ;
/* 
** Description 
*/
void	rt_destroy(t_rt_mlx *rt)
{
	scene_clear(&rt->scene);
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
}