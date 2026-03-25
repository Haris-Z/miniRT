/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:47:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:47:34 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include <rt_error.h>
#include "libft.h"

int	scene_objs_push(t_scene *s, t_object obj)
{
	if (scene_objs_reserve(s, s->objects_len + 1) != 0)
		return (1);
	s->objects_array[s->objects_len] = obj;
	s->objects_len += 1;
	return (0);
}

int	scene_add_sphere(t_scene *s, t_sphere sp)
{
	t_object	obj;

	ft_bzero(&obj, sizeof(obj));
	obj.type = SPHERE;
	obj.shape.sp = sp;
	obj.color = sp.color;
	return (scene_objs_push(s, obj));
}

int	scene_add_plane(t_scene *s, t_plane pl)
{
	t_object	obj;

	ft_bzero(&obj, sizeof(obj));
	obj.type = PLANE;
	obj.shape.pl = pl;
	obj.color = pl.color;
	return (scene_objs_push(s, obj));
}

int	scene_add_cylinder(t_scene *s, t_cylinder cy)
{
	t_object	obj;

	ft_bzero(&obj, sizeof(obj));
	obj.type = CYLINDER;
	obj.shape.cy = cy;
	obj.color = cy.color;
	return (scene_objs_push(s, obj));
}

