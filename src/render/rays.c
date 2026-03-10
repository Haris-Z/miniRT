/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/10 18:52:42 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"

static void	update_ray_dist(t_rt_mlx *vars, t_obj *obj)
{
	int		j;
	double	dist;

	j = -1;
	while (++j < vars->cam.pixels[0])
	{
		if (obj->type == OBJ_SPHERE)
			dist = hit_sp(vars->cam.pos,
					vars->cam.rays[j].direction, &obj->sphere);
		else if (obj->type == OBJ_PLANE)
			dist = hit_pl(vars->cam.pos,
					vars->cam.rays[j].direction, obj->plane);
		else if (obj->type == OBJ_CYLINDER)
			dist = hit_cy(vars->cam.pos,
					vars->cam.rays[j].direction,
					&obj->cylinder);
		if (dist > 0 && (vars->cam.rays[j].dist == -1.0
				|| dist < vars->cam.rays[j].dist))
		{
			vars->cam.rays[j].dist = dist;
			vars->cam.rays[j].closestitem = obj;
		}
	}
}
#include "debug_print.h"
#include <stdio.h>
int	render(t_scene scene_info, t_rt_mlx *app)
{
	int	i;
	int	j;
	int	k;
	if (!dir_vector_init(&(app->cam)))
		return (rt_error_msg("malloc\n"), 0);	
	i = -1;
	while (++i < app->cam.pixels[1])
	{
		add_dir_vector_row(&(app->cam));
		k = -1;
		while (++k < scene_info.objs_n)
			update_ray_dist(app, &((*(*app).cam.items)[k]));
		j = -1;
		while (++j < app->cam.pixels[0])
		{
			if (app->cam.rays[j].closestitem)
				app->img.addr[i * app->w + j] = color_to_mlx(
						compute_color(*app, app->cam.rays[j], app->cam.items));
			// print_vector("	",app->cam.rays[j].direction);
		}
	}
	return (1);
}
