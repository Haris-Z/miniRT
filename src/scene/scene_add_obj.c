/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:47:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 19:45:29 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scene.h"
#include <rt_error.h>

static t_obj	*obj_new(t_obj_type type)
{
	t_obj	*o;

	o = (t_obj *)malloc(sizeof(*o));
	if (!o)
	{
		rt_error_msg(strerror(errno));
		return (NULL);
	}
	o->type = type;
	o->next = NULL;
	return (o);
}

int	scene_add_sphere(t_scene *s, t_sphere sp)
{
	t_obj	*o;

	o = obj_new(OBJ_SPHERE);
	if (!o)
	{
		rt_error_msg(strerror(errno));
		return (1);
	}
	o->u.sp = sp;
	o->next = s->objs;
	s->objs = o;
	s->obj_count++;
	return (0);
}

int	scene_add_plane(t_scene *s, t_plane pl)
{
	t_obj	*o;

	o = obj_new(OBJ_PLANE);
	if (!o)
	{
		rt_error_msg(strerror(errno));
		return (1);
	}
	o->u.pl = pl;
	o->next = s->objs;
	s->objs = o;
	s->obj_count++;
	return (0);
}

int	scene_add_cylinder(t_scene *s, t_cylinder cy)
{
	t_obj	*o;

	o = obj_new(OBJ_CYLINDER);
	if (!o)
	{
		rt_error_msg(strerror(errno));
		return (1);
	}
	o->u.cy = cy;
	o->next = s->objs;
	s->objs = o;
	s->obj_count++;
	return (0);
}