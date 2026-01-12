/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_default_objs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:03:29 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 14:03:19 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cam.h"
#include "hit.h"
#include "vec.h"


// diffuse:
// light_dir = normalize(light.pos - hit_point)
// ndotl = max(0, dot(n, L)) 
// diffuse = albedo * light.color * (light.bright * ndotl)

//								t_hit *hit.p hit.n hit.albedo
static t_color	calc_diffuse(t_scene *s, t_vec3 point,
							t_vec3 normal, t_color albedo)
{
	t_vec3	light_dir;
	double	ndotl;
	double	intensity;
	
	if (!s->has_light)
		return ((t_color){0.0, 0.0, 0.0});
	light_dir = vec_norm(vec_sub(s->light.pos, point));
	ndotl = fmax(0.0, vec_dot(normal, light_dir));//
	intensity = s->light.bright * ndotl;
	return (vec_scale(albedo, intensity));
}

// ambient: albedo * amb.color * amb.ratio
static t_color	calc_ambient(t_scene *s, t_color albedo)
{
	if (!s->has_ambient)
		return ((t_color){0.0, 0.0, 0.0});
	return (vec_scale(vec_mul(albedo, s->amb.color), s->amb.ratio));
}

static t_color	shade_hit(t_scene *s, t_hit hit, t_color albedo)
{
	t_color	final;
	t_color	ambient;
	t_color	diffuse;

	ambient = calc_ambient(s, albedo);
	diffuse = calc_diffuse(s, hit.p, hit.n, albedo);
	final = vec_add(ambient, diffuse);
	return (final);
}

void	rt_render_default_objs(t_rt_mlx *rt)
{
	int				x;			//
	int				y;			//
	t_cam_rt		cam_rt;		// all to one struct?
	t_ray			ray;		//
	t_hit			hit;		// ray + hit one struct?

	if (!rt || !rt->img.ptr)											// checked in rt_init - during 
		return ;
	if (!rt->scene.objs || rt->scene.objs->type != OBJ_SPHERE) 			// checked during parsing remove type test later
		return ;														// checked in scene_add_obj.c remove later
	if (cam_init(&rt->scene.cam, rt->img.img_w, rt->img.img_h, &cam_rt) != 0)
		return ;
	y = 0;
	while (y < rt->img.img_h)
	{
		x = 0;
		while (x < rt->img.img_w)
		{
			// move block into another function
			ray = cam_generate_ray(cam_rt, x, y);
			// check for intersection in sphere 
			if (hit_scene_objs(&rt->scene, ray, 1e-4, 1e30, &hit))
				hit.color = shade_hit(&rt->scene, hit, rt->scene.objs->u.sp.color);
			else
				hit.color = (t_color){0.0, 0.0, 0.0}; // Background color
			rt_img_put_pixel(&rt->img, x, y, color_to_mlx(hit.color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.ptr, 0, 0);
}
