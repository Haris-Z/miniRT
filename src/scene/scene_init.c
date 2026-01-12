/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:50:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 13:34:32 by hazunic          ###   ########.fr       */
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
 * @note remove defaults
 * 
 * @param s
 */
void	scene_init(t_scene *s)
{
	if (!s)
		return ;
	// ft_bzero() return ;
	s->has_ambient = 0;
	s->has_camera = 0;
	s->has_light = 0;
	s->amb.ratio = 0.0;
	s->amb.color = color_rgb(255, 255, 255); // Default white
	//s->amb.color = color_rgb(0,0,0); // Default black
	s->cam.pos = vec3(0.0, 0.0, 0.0);	// Default
	s->cam.dir = vec3(0.0, 0.0, 0.0);	// Default
	s->cam.fov_deg = 0.0;						// Default
	s->light.pos = vec3(0.0, 0.0, 0.0);	// Default
	s->light.bright = 0.0;
	s->light.color = color_rgb(255, 255, 255);	// Default white
	s->light.color = color_rgb(0, 0, 0);	// Default black
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
// remove before submissoin
int	set_default_scene_sphere(t_scene *s)
{
	t_sphere	sp;
	t_sphere	sp2;
	t_sphere	sp3;
	t_sphere	sp4;

	if (!s)
		return (1);
	ft_bzero(&sp, sizeof(sp));
	
	s->has_ambient = 1;
	s->has_camera = 1;
	s->has_light = 1;
	
	s->amb.ratio = 0.3;
	s->amb.color = color_rgb(255, 255, 255);			// Default
	// s->amb.color = color_rgb(10, 0, 255);				  // Default

	s->cam.pos = vec3(0, 0, -5);			       // Default
	s->cam.dir = vec3(0,0,1);		       // Default
	//s->cam.dir = vec_norm(vec3(0,0,1));		       // Default
	s->cam.fov_deg = 70;									 // Default ->int
	
	//s->light.pos = vec3(5, 5, -2);	// Default
	s->light.pos = vec3(-10, 10, 10);	// Default
	// s->light.pos = vec3(-40.0, 50.0, 0.0);	// Default
	s->light.bright = 0.8;
	// not mandatory part - add later
	//s->light.color = color_rgb(255, 255, 255);

	//sp.center = vec3(0.0, 0.0, 0.0);
	sp.center = vec3(0.0, 0.0, 20.0);
	sp.diameter = 6.3;
	sp.radius = sp.diameter * 0.5;
	// sp.diameter = 4.0;
	// sp.radius = sp.diameter * 0.5;
	// sp.color = color_rgb(255,0,0);
	sp.color = color_rgb(10,0,255);


	sp2.center = vec3(5, 0.0, 20.0);
	sp2.diameter = 6.3;
	sp2.radius = sp.diameter * 0.5;
	sp2.color = color_rgb(10, 0, 255);


	sp3.center = vec3(-5, 0, 20.0);
	sp3.diameter = 6.3;
	sp3.radius = sp.diameter * 0.5;
	sp3.color = color_rgb(10, 0, 255);


	sp4.center = vec3(0, 5, 20.0);
	sp4.diameter = 6.3;
	sp4.radius = sp.diameter * 0.5;
	sp4.color = color_rgb(10, 0, 255);
	// point at sphere if not in view.
	// or set scene correctly
	//s->cam.dir = vec_norm(vec_sub(sp.center, s->cam.pos));
	if (scene_add_sphere(s, sp) != 0)
		return (1);
	if (scene_add_sphere(s, sp2) != 0)
		return (1);
	if (scene_add_sphere(s, sp3) != 0)
		return (1);
	if (scene_add_sphere(s, sp4) != 0)
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