/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 23:14:46 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"

static void	update_ray_dist(t_cam_rt cam, t_object *obj, t_ray *ray)
{
	double	dist;

	dist = 0.0; 
	if (obj->type == SPHERE)
		dist = hit_sp(cam.pos,
				ray->direction, &obj->shape.sp);
	else if (obj->type == PLANE)
		dist = hit_pl(cam.pos,
				ray->direction, obj->shape.pl);
	else if (obj->type == CYLINDER)
		dist = hit_cy(cam.pos,
				ray->direction,
				&obj->shape.cy);
	if (dist > 0.0 && (ray->dist == -1.0
			|| dist < ray->dist))
	{
		ray->dist = dist;
		ray->closestitem = obj;
	}
}

t_color	color_mix(t_color *arr, int len)
{
	t_color	res;
	int		i;

	res = vec3(0, 0, 0);
	i = -1;
	while (++i < len)
		res = vec_add(res, arr[i]);
	res.x /= len;
	res.y /= len;
	res.z /= len;
	return (res);
}
#include <stdio.h>
#include "debug_print.h"
int	render(t_scene *s, t_rt_mlx *app)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	t_ray	dir;
	t_color	buf[MSAA * MSAA];
	double	pixel_start[2];
	double	pre_calc[4];

	app->cam = cam_init(*s, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!dir_vector_init(&(app->cam)))
		return (rt_error_msg("malloc\n"), 0);
	pre_calc[0] = sin(app->cam.vp.horOffset);
	pre_calc[1] = cos(app->cam.vp.horOffset);
	i = -1;
	pixel_start[0] = app->cam.vp.verRange;
	printf("deltaH %.6f deltaV %.6f/n", app->cam.vp.deltaVerRange,app->cam.vp.deltaHorAngle);
	while (++i < (app->cam.pixels[1]))
	{
		pixel_start[1] = app->cam.vp.horRange;
		j = -1;
		while (++j < (app->cam.pixels[0]))
		{
			pre_calc[2] = pixel_start[0];
			l = -1;
			while (++l < MSAA)
			{
				pre_calc[3] = pixel_start[1];
				m = -1;
				while (++m < MSAA)
				{
					dir = get_dir_vector(&app->cam, pre_calc);
					k = -1;
					while (++k < s->objects_len)
						update_ray_dist(app->cam, &s->objects_array[k], &dir);
					if (dir.closestitem)
						buf[(l * MSAA) + m] = compute_color(*app, dir, s->objects_array, s->objects_len);
					else
						buf[(l * MSAA) + m] = color_rgb(0, 0, 0);
					pre_calc[3] -= app->cam.vp.deltaHorAngle;
				}
				pre_calc[2] -= app->cam.vp.deltaVerRange;
			}
			app->img.addr[i * app->w + j] = color_to_mlx(color_mix(buf, MSAA * MSAA));
			pixel_start[1] = pre_calc[3]; 
		}
		pixel_start[0] = pre_calc[2];
	}
	return (1);
}
