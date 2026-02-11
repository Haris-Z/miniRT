/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/08 15:20:35 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

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

void	render(t_scene scene_info, t_rt_mlx app)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < app.cam.pixels[1])
	{
		add_dir_vector_row(&app.cam);
		k = -1;
		while (++k < scene_info.objs_n)
			update_ray_dist(&app, &((*app.cam.items)[k]));
		j = -1;
		while (++j < app.cam.pixels[0])
		{
			if (app.cam.rays[j].closestitem)
				app.img.addr[i * app.w + j] = color_to_mlx(
						compute_color(app, app.cam.rays[j], app.cam.items));
		}
	}
}
