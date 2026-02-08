/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:25:53 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/08 17:52:36 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "stdio.h"
#include "libft.h"

void	print_scene_info(t_scene scene, char *file)
{
	printf("=========================   PARSED SCENE (%s) ==========================================================================\n\n", ft_strrchr(file, '/') + 1);
	
	printf("=========================  ELEMENTS  ==========================================================================\n\n");
	if (scene.has_ambient)
		printf("Ambient: ratio=%.2f			| color=(r=%f,g=%f,b=%f)\n \
					| color=%d | colorhex=0x%X\n\n",
			   scene.amb.ratio, scene.amb.color.x, scene.amb.color.y, scene.amb.color.z, scene.amb.rgb, scene.amb.rgb);
	if (scene.has_camera)
		printf("Camera:	 pos(x=%.2f,y=%.2f,z=%.2f)	| dir(x=%.2f,y=%.2f,z=%.2f)	| fov=%.1f°\n\n",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z,
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z,
			   scene.cam.fov_deg);
	if (scene.has_light)
		printf("Light:	 pos(%.2f,%.2f,%.2f)		| brightness=%.2f		| color=(%f,%f,%f) \n\
									| color=%d | colorhex=0x%X\n",
			   scene.light.pos.x, scene.light.pos.y, scene.light.pos.z,
			   scene.light.bright, scene.light.color.x, scene.light.color.y, scene.light.color.z, scene.light.rgb, scene.light.rgb);
	printf("=========================  OBJECTS  ============================================================================\n\n");
	t_obj *obj = scene.objs;
	int i = 0;
	while (obj)
	{
		printf("  - ");
		if (obj->type == OBJ_SPHERE)
			printf("Sphere:     center(%.2f,%.2f,%.2f) | radius=%.2f | sp.color=(%f,%f,%f) |\n",
				   obj->sphere.center.x, obj->sphere.center.y, obj->sphere.center.z,
				   obj->sphere.radius, obj->sphere.color.x, obj->sphere.color.y, obj->sphere.color.z
				);
		else if (obj->type == OBJ_PLANE)
			printf("Plane:      point(%.2f,%.2f,%.2f) | normal(%.2f,%.2f,%.2f) | pl.color=(%f,%f,%f) |\n",
					obj->plane.point.x, obj->plane.point.y, obj->plane.point.z,
					obj->plane.normal.x, obj->plane.normal.y, obj->plane.normal.z, \
					obj->plane.color.x, obj->plane.color.y, obj->plane.color.z
				);
		else if (obj->type == OBJ_CYLINDER)
			printf("Cylinder:   center(%.2f,%.2f,%.2f) | axis=(%.2f,%.2f,%.2f) | diameter=%.2f | height=%.2f | cy.color=(%f,%f,%f) |\n",
				   obj->cylinder.center.x, obj->cylinder.center.y, obj->cylinder.center.z, \
				   obj->cylinder.axis.x, obj->cylinder.axis.y, obj->cylinder.axis.z, \
				   obj->cylinder.diameter, obj->cylinder.height, \
				obj->cylinder.color.x, obj->cylinder.color.y, obj->cylinder.color.z);
		i++;
		obj = obj->next;
	}
	printf("=============================================================\n");
	printf("Objects: %d\n", i);
	printf("=============================================================\n");
}

void	print_vector(char *name, t_vec3 v)
{
	if (name)
		printf("%s: ", name);
	printf("(%.2f, %.2f, %.2f)", v.x, v.y, v.z);
	printf("\n");
}

void	printV(t_vec3 a)
{
	printf("x: %f y: %f z: %f\n", a.x,a.y,a.z);
}

void	printM(t_mat3 a)
{
	printf("	%f	%f	%f\n", a.colx.x, a.coly.x, a.colz.x);
	printf("	%f	%f	%f\n", a.colx.y, a.coly.y, a.colz.y);
	printf("	%f	%f	%f\n", a.colx.z, a.coly.z, a.colz.z);
}

void	print_epsilon(double multiplier)
{
	if (multiplier >= 1)
		printf("EPSILON * %.12f = %.12f\n", multiplier, EPSILON * multiplier);
	else
		printf("EPSILON = %.12f\n", EPSILON);
}