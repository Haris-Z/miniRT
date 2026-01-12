/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:00:39 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 13:36:06 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "ray.h"
#include "hit.h"

// closest hit across all objects
int	hit_scene_objs(t_scene *s, t_ray r, double tmin, double tmax, t_hit *h)
{
	t_obj	*o;
	t_hit	tmp;
	double	closest;
	int		hit_any;

	o = s->objs;
	closest = tmax;
	hit_any = 0;
	while (o)
	{
		if (o->type == OBJ_SPHERE && hit_sphere(&o->u.sp, r, tmin, closest, &tmp))
		{
			*h = tmp;
			closest = tmp.t;
			hit_any = 1;
		}
		// else if (o->type == OBJ_PLANE && hit_plane(&o->u.pl, r, tmin, closest, &tmp))
		// {
		// 	*h = tmp;
		// 	closest = tmp.t;
		// 	hit_any = 1;
		// }
		// else if (o->type == OBJ_CYLINDER && hit_cylinder(&o->u.cy, r, tmin, closest, &tmp))
		// {
		// 	*h = tmp;
		// 	closest = tmp.t;
		// 	hit_any = 1;
		// }
		o = o->next;
	}
	return (hit_any);
}