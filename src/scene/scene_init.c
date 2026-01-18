/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:50:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/18 06:01:12 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "color.h"
#include "scene.h"
#include "libft.h"
#include "vec.h"

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


/*
A	0.2 255,255,255
C	-50,0,20 0,0,1 70
L	-40,0,50 0.6 10,0,255
sp	0,0,20.6 12.6 10,0,255
	not tested yet.
*/
// remove before submissoin
int	set_default_scene(t_scene *s)
{
	t_ambient	a;
	t_camera	c;
	t_light		l;
	
	t_sphere	sp;
	t_sphere	sp2;
	t_sphere	sp3;
	t_sphere	sp4;
	t_sphere	sp5;

	if (!s)
		return (1);
	ft_bzero(&sp, sizeof(sp));
	
	a.ratio = 0.8;
	a.color = color_rgb(0, 0, 0);

	c.pos = vec3(0, 0, -10);
	c.dir = vec3(0,0,1);
	c.fov_deg = 70;

	l.pos = vec3(-10, 10, 10);
	l.bright = 0.8;
	l.color = color_rgb(255, 255, 255);

	scene_set_ambient(s, a);
	scene_set_camera(s, c);
	scene_set_light(s, l);


	sp.center = vec3(0.0, 0.0, 20.0);
	sp.diameter = 6.3;
	sp.radius = sp.diameter * 0.5;
	sp.color = color_rgb(255,0,0);
	if (scene_add_sphere(s, sp) != 0)
		return (1);

	sp2.center = vec3(5, 0.0, 20.0);
	sp2.diameter = 6.3;
	sp2.radius = sp.diameter * 0.5;
	sp2.color = color_rgb(0, 255, 0);
	if (scene_add_sphere(s, sp2) != 0)
		return (1);

	sp3.center = vec3(-5, 0, 20.0);
	sp3.diameter = 6.3;
	sp3.radius = sp.diameter * 0.5;
	sp3.color = color_rgb(0, 0, 255);
	if (scene_add_sphere(s, sp3) != 0)
		return (1);

	sp4.center = vec3(0, 5, 20.0);
	sp4.diameter = 6.3;
	sp4.radius = sp.diameter * 0.5;
	sp4.color = color_rgb(150, 150, 150);
	if (scene_add_sphere(s, sp4) != 0)
		return (1);

	sp5.center = vec3(0, -5, 20.0);
	sp5.diameter = 6.3;
	sp5.radius = sp.diameter * 0.5;
	sp5.color = color_rgb(255, 255, 255);
	if (scene_add_sphere(s, sp5) != 0)
		return (1);
	return (0);
}


void	scene_clear(t_scene *s)
{
	if (!s)
		return ;
	obj_free_list(s->objs);
	s->objs = NULL;
	// reset rest?
}