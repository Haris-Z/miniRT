/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:37:08 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"

static void	update_ray_dist(t_rt_mlx *vars, t_object *obj)
{
	int		j;
	double	dist;

	j = -1;
	while (++j < vars->w)
	{
		if (obj->type == SPHERE)
			dist = hit_sp(vars->cam.pos,
					vars->cam.rays[j].direction, &obj->shape.sp);
		else if (obj->type == PLANE)
			dist = hit_pl(vars->cam.pos,
					vars->cam.rays[j].direction, obj->shape.pl);
		else if (obj->type == CYLINDER)
			dist = hit_cy(vars->cam.pos,
					vars->cam.rays[j].direction,
					&obj->shape.cy);
		if (dist > 0 && (vars->cam.rays[j].dist == -1.0
				|| dist < vars->cam.rays[j].dist))
		{
			vars->cam.rays[j].dist = dist;
			vars->cam.rays[j].closestitem = obj;
		}
	}
}

#include "debug_print.h"

int	render(t_scene *s, t_rt_mlx *app) // pass only obj-array and len
{
	int	i;
	int	j;
	int	k;

	app->cam = s->cam;
	if (!dir_vector_init(&(app->cam), app->w, app->h))
		return (rt_error_msg("malloc\n"), 0);
	i = -1;
	while (++i < app->h)
	{
		add_dir_vector_row(&(app->cam), app->w);
		k = -1;
		while (++k < s->objects_len)
			update_ray_dist(app, &s->objects_array[k]);
		j = -1;
		while (++j < app->w)
		{
			if (app->cam.rays[j].closestitem)
				app->img.addr[i * app->w + j] = color_to_mlx(
						compute_color(*s, app->cam.rays[j]));
			// print_vector("	",app->cam.rays[j].direction);
		}
	}
	return (1);
}
