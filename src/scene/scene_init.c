/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:50:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/10 12:28:47 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scene.h"

static void	obj_free_list(t_obj *o)
{
	t_obj	*next;

	while (o)
	{
		next = o->next;
		free(o);
		o = next;
	}
}

/**
 * @brief	initialze scene struct for parsing
 * 
 * 
 * @note defaults can be set without parsing a file
 * 
 * @param s
 */
void	scene_init(t_scene *s)
{
	s->has_ambient = 0;
	s->has_camera = 0;
	s->has_light = 0;
	s->amb.ratio = 0.0;
	s->amb.color = vec3(0.0, 0.0, 0.0); // Default
	s->cam.pos = vec3(0.0, 0.0, 0.0);	// Default
	s->cam.dir = vec3(0.0, 0.0, 1.0);	// Default
	s->cam.fov_deg = 60.0;						// Default
	s->light.pos = vec3(0.0, 0.0, 0.0);	// Default
	s->light.bright = 0.0;
	s->light.color = vec3(1.0, 1.0, 1.0);	// Default
	s->objs = NULL; // Set default if needed
	s->obj_count = 0;
}

void	scene_clear(t_scene *s)
{
	obj_free_list(s->objs);
	s->objs = NULL;
	s->obj_count = 0;
}