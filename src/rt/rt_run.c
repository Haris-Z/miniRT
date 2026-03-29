/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:29:17 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 16:28:18 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/* 
** events and mask found in <X11/X.h>
*/
int	rt_run(t_rt_mlx *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, rt_on_keypress, rt);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, rt_on_destroy, rt);
	mlx_expose_hook(rt->win, rt_on_expose, rt);
	mlx_loop(rt->mlx);
	rt_destroy(rt);
	return (0);
}
