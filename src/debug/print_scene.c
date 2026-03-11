/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:19 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:21:13 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "debug_print.h"

static void	pelements(t_scene scene);
static void	pobjects(t_scene scene);

void	print_scene_info(t_scene scene, char *file)
{
	printf("========== PARSED SCENE (%s) ===========\n\n", ft_strrchr(file, '/') + 1);
	pelements(scene);
	printf("==========  OBJECTS  ==========\n\n");
	pobjects(scene);
}

static void	pelements(t_scene scene)
{
	printf("==========  ELEMENTS  ==========\n\n");
	if (scene.has_ambient)
		printf("Ambient: ratio=%.2f			| color=(r=%f,g=%f,b=%f)\n \
					| color=%d | colorhex=0x%X\n\n",
			   scene.amb.ratio, \
			   scene.amb.color.x, \
			   scene.amb.color.y, \
			   scene.amb.color.z, color_to_int(scene.amb.color), color_to_int(scene.amb.color));
	if (scene.has_camera)
		printf("Camera:	 pos(x=%.2f,y=%.2f,z=%.2f)	| dir(x=%.2f,y=%.2f,z=%.2f)	| fov=%.1f°\n\n",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z,
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z,
			   scene.cam.fov_deg);
	if (scene.has_light)
		printf("Light:	 pos(%.2f,%.2f,%.2f)		| brightness=%.2f		| color=(%f,%f,%f) \n\
									| color=%d | colorhex=0x%X\n",
			   scene.light.pos.x, scene.light.pos.y, scene.light.pos.z,
			   scene.light.bright, \
			   scene.light.color.x, \
			   scene.light.color.y, \
			   scene.light.color.z, \
			   color_to_int(scene.light.color), color_to_int(scene.light.color));
}

static void	pobjects(t_scene scene)
{
	int			i;
	t_object	*obj;

	obj = scene.objects_array;
	i = -1;
	while (++i < scene.objects_len / 2)
	{
		printf("  - ");
		if (obj->type == SPHERE)
			printf("SP: cxyz(%.2f,%.2f,%.2f) | r=%.2f | crgb=(%f,%f,%f) |\n",
				obj->shape.sp.center.x, obj->shape.sp.center.y, obj->shape.sp.center.z,
				obj->shape.sp.radius, obj->shape.sp.color.x, obj->shape.sp.color.y, obj->shape.sp.color.z
				);
		else if (obj->type == PLANE)
			printf("PL:  pxyz(%.2f,%.2f,%.2f) | nxyz(%.2f,%.2f,%.2f) | crgb=(%f,%f,%f) |\n",
					obj->shape.pl.point.x, obj->shape.pl.point.y, obj->shape.pl.point.z,
					obj->shape.pl.normal.x, obj->shape.pl.normal.y, obj->shape.pl.normal.z, \
					obj->shape.pl.color.x, obj->shape.pl.color.y, obj->shape.pl.color.z
				);
		else if (obj->type == CYLINDER)
			printf("CY: cxyz(%.2f,%.2f,%.2f) | axyz=(%.2f,%.2f,%.2f) | d=%.2f | h=%.2f | crgb=(%f,%f,%f) |\n",
				obj->shape.cy.center.x, obj->shape.cy.center.y, obj->shape.cy.center.z, \
				obj->shape.cy.axis.x, obj->shape.cy.axis.y, obj->shape.cy.axis.z, \
				obj->shape.cy.diameter, obj->shape.cy.height, \
				obj->shape.cy.color.x, obj->shape.cy.color.y, obj->shape.cy.color.z);
	}
	printf("------\nObjects: %d------\n", i);
}
