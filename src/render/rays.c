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
	while (++j < vars->cam.pixels[0])
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

	app->cam = cam_init(*s, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!dir_vector_init(&(app->cam)))
		return (rt_error_msg("malloc\n"), 0);
	printf("deltaH %.6f deltaV %.6f\n", app->cam.vp.deltaVerRange,app->cam.vp.deltaHorAngle);
	i = -1;
	while (++i < app->cam.pixels[1])
	{
		add_dir_vector_row(&(app->cam));
		k = -1;
		while (++k < s->objects_len)
			update_ray_dist(app, &s->objects_array[k]);
		j = -1;
		while (++j < app->cam.pixels[0])
		{
			if (app->cam.rays[j].closestitem)
				app->img.addr[i * app->w + j] = color_to_mlx(
						compute_color(*app, app->cam.rays[j], s->objects_array, s->objects_len));
			// print_vector("	",app->cam.rays[j].direction);
		}
	}
	return (1);
}
