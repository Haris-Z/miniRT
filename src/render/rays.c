/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:53:31 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	updateRayDist(t_rt_mlx *vars, t_obj *obj)
{
	int	j;
	double	dist;

	j = -1;
	while(++j < vars->cam.pixels[0])
	{
		if (obj->type == OBJ_SPHERE)
			dist = hitSp(vars->cam.pos, vars->cam.rays[j].direction, &obj->sphere);
		else if (obj->type == OBJ_PLANE)
			dist = hitPl(vars->cam.pos, vars->cam.rays[j].direction, obj->plane);
		if (dist > 0 && (vars->cam.rays[j].dist == -1.0 || dist < vars->cam.rays[j].dist))
		{
			vars->cam.rays[j].dist = dist;
			vars->cam.rays[j].closestitem = obj;
		}
	}
}

