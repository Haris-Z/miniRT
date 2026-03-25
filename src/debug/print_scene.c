/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:19 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 21:24:56 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "debug_print.h"

/*
		DELETE BEFORE SUBMISSION, JUST FOR PRINTING IN DEBUG
*/

static void	pelements(t_scene scene);
static void	pobjects(t_scene scene, int *i);
static void	print_sep(char c, int len);

void	print_scene_info(t_scene scene, char *file)
{
	int	i;

	print_sep('=', 114);
	printf("PARSED SCENE (%s)\n", ft_strrchr(file, '/') + 1);
	print_sep('=', 114);
	printf("ELEMENTS\n");
	print_sep('=', 114);
	pelements(scene);
	print_sep('=', 114);
	printf("OBJECTS\n");
	print_sep('=', 114);
	pobjects(scene, &i);
	print_sep('=', 114);
	printf("Objects: %d/%d\n", i, scene.objects_len);
	print_sep('=', 114);
}

static void	pelements(t_scene scene)
{
	size_t	i;

	if (scene.has_ambient)
	{
		printf("Ambient:\f\r\t\tratio = %.2f\n", scene.amb.ratio);
		print_vector("\t\tcolor", scene.amb.color);
	}
	if (scene.has_camera)
	{
		printf("\nCamera:\f\r");
		print_vector("\t\tpos", scene.cam.pos);
		print_vector("\t\tdir", scene.cam.dir);
		printf("\t\tfov = %.1f\n", scene.cam.fov_deg);
	}
	if (scene.has_light)
	{
		i = -1;
		while (++i < scene.light_count)
		{
			printf("Light[%zu]:\f\r", i);
			print_vector("\t\tpos", scene.light[i].pos);
			printf("\t\tbrightness = %.2f\n", scene.light[i].bright);
			print_vector("\t\tcolor", scene.light[i].color);
		}
	}
}

static void	pobjects(t_scene scene, int *ct)
{
	int			i;
	t_object	*obj;

	obj = scene.objects_array;
	i = -1;
	while (++i < scene.objects_len)//while (++i < scene.objects_len / 2)
	{
		if (obj[i].type == SPHERE)
		{
			printf("SP[%d]:",i);
			print_vector("\tcxyz", obj[i].shape.sp.center);
			printf("\t\tr = %.2f\n", obj[i].shape.sp.radius);
			print_vector("\t\trgb", obj[i].shape.sp.color);
		}
		else if (obj[i].type == PLANE)
		{
			printf("PL[%d]:",i);
			print_vector("\tpxyz", obj[i].shape.pl.point);
			print_vector("\t\tnxyz", obj[i].shape.pl.normal);
			print_vector("\t\trgb", obj[i].shape.pl.color);
		}
		else if (obj[i].type == CYLINDER)
			printf("CY: cxyz(%.2f,%.2f,%.2f)	| axyz=(%.2f,%.2f,%.2f) | d=%.2f | h=%.2f\t| crgb=(%f,%f,%f) |\n",
				obj[i].shape.cy.center.x, obj[i].shape.cy.center.y, obj[i].shape.cy.center.z, \
				obj[i].shape.cy.axis.x, obj[i].shape.cy.axis.y, obj[i].shape.cy.axis.z, \
				obj[i].shape.cy.diameter, obj[i].shape.cy.height, \
				obj[i].shape.cy.color.x, obj[i].shape.cy.color.y, obj[i].shape.cy.color.z);
	}
	*ct = i;
}

static void	print_sep(char sep, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		printf("%c", sep);
	printf("\n");
}