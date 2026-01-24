/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:47:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:49:42 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include <rt_error.h>
#include "libft.h"

static t_obj	*obj_new(t_type type)
{
	t_obj	*o;

	o = (t_obj *)ft_calloc(1, sizeof(*o));
	if (!o)
		return (NULL);
	o->type = type;
	o->next = NULL;
	return (o);
}

int	scene_add_sphere(t_scene *s, t_sphere sp)
{
	t_obj	*o;

	o = obj_new(OBJ_SPHERE);
	if (!o)
		return (1);
	o->sphere = sp;
	o->color = color_to_int(sp.color);
	o->next = s->objs;
	s->objs = o;
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
	o->plane = pl;
	o->color = color_to_int(pl.color);
	o->next = s->objs;
	s->objs = o;
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
	o->cylinder = cy;
	o->color = color_to_int(cy.color);
	o->next = s->objs;
	s->objs = o;
	return (0);
}