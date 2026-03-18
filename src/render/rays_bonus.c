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

static void	update_ray_dist(t_camera cam, t_object *obj, t_ray *ray)
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

t_color	c_mix(t_color *arr, int len)
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

static void	get_pixel_color(t_rt_mlx *app, t_scene *s,
		double pre_calc[6], t_color buf[])
{
	int		k;
	t_ray	dir;
	int		l;
	int		m;

	pre_calc[2] = pre_calc[4];
	l = -1;
	while (++l < MSAA)
	{
		pre_calc[3] = pre_calc[5];
		m = -1;
		while (++m < MSAA)
		{
			dir = get_dir_vector(&app->cam, pre_calc);
			k = -1;
			while (++k < s->objects_len)
				update_ray_dist(app->cam, &s->objects_array[k], &dir);
			if (dir.closestitem)
				buf[(l * MSAA) + m] = compute_color(*s, dir);
			else
				buf[(l * MSAA) + m] = color_rgb(0, 0, 0);
			pre_calc[3] -= app->cam.vp.delta_hor_angle;
		}
		pre_calc[2] -= app->cam.vp.delta_ver_range;
	}
}

// precalc: 0 - sinOffset, 1 - cosOffset, 2,3 - pos h,w  4,5 - pixelstart h,w
int	render(t_scene *s, t_rt_mlx *app)
{
	int		i;
	int		j;
	double	pre_calc[6];
	t_color	buf[MSAA * MSAA];

	app->cam = s->cam;
	if (!dir_vector_init(&(app->cam), app->w, app->h))
		return (rt_error_msg("malloc\n"), 0);
	pre_calc[0] = sin(app->cam.vp.hor_offset);
	pre_calc[1] = cos(app->cam.vp.hor_offset);
	i = -1;
	pre_calc[4] = app->cam.vp.ver_range;
	while (++i < (app->h))
	{
		pre_calc[5] = app->cam.vp.hor_range;
		j = -1;
		while (++j < (app->w))
		{
			get_pixel_color(app, s, pre_calc, buf);
			app->img.addr[i * app->w + j] = c_to_mlx(c_mix(buf, MSAA * MSAA));
			pre_calc[5] = pre_calc[3];
		}
		pre_calc[4] = pre_calc[2];
	}
	return (1);
}
