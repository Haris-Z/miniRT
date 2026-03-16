/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:19 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 20:53:11 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "debug_print.h"

/*
		DELETE BEFORE SUBMISSION, JUST FOR PRINTING IN DEBUG
*/

static void	pelements(t_scene scene);
static void	pobjects(t_scene scene);
static void	print_sep(char c, int len);

void	print_scene_info(t_scene scene, char *file)
{
	print_sep('=', 114);
	printf("PARSED SCENE (%s)\n", ft_strrchr(file, '/') + 1);
	print_sep('=', 114);
	printf("ELEMENTS\n");
	print_sep('=', 114);
	pelements(scene);
	print_sep('=', 114);
	printf("OBJECTS\n");
	print_sep('=', 114);
	pobjects(scene);
}

static void	pelements(t_scene scene)
{
	size_t	i;

	if (scene.has_ambient)
		printf("Ambient: ratio = %.2f\f\r\t\t color = (r=%f,g=%f,b=%f)", scene.amb.ratio, \
			   scene.amb.color.x, \
			   scene.amb.color.y, \
			   scene.amb.color.z);
	if (scene.has_camera)
		printf("\n\nCamera:\t pos = (x=%.2f, y=%.2f, z=%.2f)\f\r\t\t dir = (x=%.2f,y=%.2f,z=%.2f)\f\r\t\t fov = %.1f°",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z,
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z,
			   scene.cam.fov_deg);
	printf("\n\n");
	if (scene.has_light)
	{
		i = -1;
		while (++i < scene.light_count)
		printf("Light:\t pos(%.2f,%.2f,%.2f) \t | brightness=%.2f \t | color=(%f,%f,%f)\n", \
			   scene.light[i].pos.x, scene.light[i].pos.y, scene.light[i].pos.z,
			   scene.light[i].bright, \
			   scene.light[i].color.x, \
			   scene.light[i].color.y, \
			   scene.light[i].color.z \
			   );
	}
}

static void	pobjects(t_scene scene)
{
	int			i;
	t_object	*obj;

	obj = scene.objects_array;
	
	i = -1;
	while (++i < scene.objects_len)//while (++i < scene.objects_len / 2)
	{
		if (obj[i].type == SPHERE)
			printf("SP: cxyz(%.2f,%.2f,%.2f)	| r=%.2f\t\t\t\t\t\t\t\t\t| crgb=(%f,%f,%f) |\n",
				obj[i].shape.sp.center.x, obj[i].shape.sp.center.y, obj[i].shape.sp.center.z,
				obj[i].shape.sp.radius, obj[i].shape.sp.color.x, obj[i].shape.sp.color.y, obj[i].shape.sp.color.z
				);
		else if (obj[i].type == PLANE)
			printf("PL: pxyz(%.2f,%.2f,%.2f)	| nxyz(%.2f,%.2f,%.2f)\t\t\t\t\t\t| crgb=(%f,%f,%f) |\n",
					obj[i].shape.pl.point.x, obj[i].shape.pl.point.y, obj[i].shape.pl.point.z,
					obj[i].shape.pl.normal.x, obj[i].shape.pl.normal.y, obj[i].shape.pl.normal.z, \
					obj[i].shape.pl.color.x, obj[i].shape.pl.color.y, obj[i].shape.pl.color.z
				);
		else if (obj[i].type == CYLINDER)
			printf("CY: cxyz(%.2f,%.2f,%.2f)	| axyz=(%.2f,%.2f,%.2f) | d=%.2f | h=%.2f\t| crgb=(%f,%f,%f) |\n",
				obj[i].shape.cy.center.x, obj[i].shape.cy.center.y, obj[i].shape.cy.center.z, \
				obj[i].shape.cy.axis.x, obj[i].shape.cy.axis.y, obj[i].shape.cy.axis.z, \
				obj[i].shape.cy.diameter, obj[i].shape.cy.height, \
				obj[i].shape.cy.color.x, obj[i].shape.cy.color.y, obj[i].shape.cy.color.z);
	}
	print_sep('=', 114);
	printf("Objects: %d/%d\n", i, scene.objects_len);
	print_sep('=', 114);
}

static void	print_sep(char sep, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		printf("%c", sep);
	printf("\n");
}