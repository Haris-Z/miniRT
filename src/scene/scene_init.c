/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:50:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/10 13:54:51 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "color.h"
#include "scene.h"
#include "libft.h"

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
	if (!s)
		return ;
	s->has_ambient = 0;
	s->has_camera = 0;
	s->has_light = 0;
	s->amb.ratio = 0.0;
	s->amb.color = color_rgb(0.0, 0.0, 0.0); // Default
	s->cam.pos = vec3(0.0, 0.0, 0.0);	// Default
	s->cam.dir = vec3(0.0, 0.0, 1.0);	// Default
	s->cam.fov_deg = 60.0;						// Default
	s->light.pos = vec3(0.0, 0.0, 0.0);	// Default
	s->light.bright = 0.0;
	s->light.color = color_rgb(1.0, 1.0, 1.0);	// Default
	s->objs = NULL; // Set default if needed
	s->obj_count = 0;
}

/*
A	0.2 255,255,255
C	-50,0,20 0,0,1 70
L	-40,0,50 0.6 10,0,255
sp	0,0,20.6 12.6 10,0,255

	not tested yet.
*/
int	set_default_scene_sphere(t_scene *s)
{
	t_sphere	sp;

	if (!s)
		return (1);
	ft_bzero(&sp, sizeof(sp));
	scene_clear(s);
	
	s->has_ambient = 1;
	s->has_camera = 1;
	s->has_light = 1;
	
	s->amb.ratio = 0.2;
	s->amb.color = color_rgb(255, 255, 255);	// Default
	
	s->cam.pos = vec3(-50, 1, 20);				// Default
	s->cam.dir = vec_norm(vec3(0.0,0.0,1.0));	// Default
	s->cam.fov_deg = 70.0;							   // Default
	
	s->light.pos = vec3(-40, 0, 50);	// Default
	s->light.bright = 0.6;
	s->light.color = color_rgb(10, 0, 255);	// Default

	sp.center = vec3(0.0, 0.0, 20.6);
	sp.radius = 12.6 * 0.5;
	sp.color = color_rgb(10,0,255);

	s->cam.dir = vec_norm(vec_sub(sp.center, s->cam.pos));

	if (scene_add_sphere(s, sp) != 0)
		return (1);
	return (0);
}


void	scene_clear(t_scene *s)
{
	if (!s)
		return ;
	obj_free_list(s->objs);
	s->objs = NULL;
	s->obj_count = 0;
	// reset rest?
}