/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:47:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/12 23:02:59 by hazunic          ###   ########.fr       */
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
	{
		rt_error_msg(strerror(errno));
		return (1);
	}
	o->sphere = sp;
	o->color = sp.color;
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
	o->color = pl.color;
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
	o->color = cy.color;
	o->next = s->objs;
	s->objs = o;
	return (0);
}

static int	obj_list_count(t_obj *o)
{
	int	n;

	n = 0;
	while (o)
	{
		n++;
		o = o->next;
	}
	return (n);
}

int	scene_obj_array(t_scene *s)
{
	t_obj	*o;
	int		n;
	int		i;

	if (!s)
	{
		rt_error_msg("scene_obj_array(): Invalid input param <s>");
		return (1);
	}
	n = obj_list_count(s->objs);
	if (n == 0)
		return (0);
	s->objs_arr = (t_obj *)ft_calloc(n, sizeof(*s->objs_arr));
	if (!s->objs_arr)
	{
		rt_error_msg(strerror(errno));
		return (1);
	}
	o = s->objs;
	i = 0;
	while (o)
	{
		s->objs_arr[i] = *o;
		s->objs_arr[i].next = NULL;
		i++;
		o = o->next;
	}
	s->objs_n = n;
	return (0);
}
