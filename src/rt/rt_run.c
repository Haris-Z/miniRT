/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:29:17 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/22 15:15:23 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* 
** Description ............................
** events and mask found in <X11/X.h>
*/
int	rt_run(t_rt_mlx *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, rt_on_keypress, rt);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, rt_on_destroy, rt);
	mlx_expose_hook(rt->win, rt_on_expose, rt);
	mlx_loop(rt->mlx);
	//rt_destroy(rt);
	return (0);
}
