/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:45:32 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/13 17:14:33 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "rt_error.h"
#include "trace_log.h"
#include "dbg_log.h"
#include "parser.h"
#include "scene.h"
#include "vec.h"
#include <stdio.h>


static void		print_rt_file_content(t_scene scene);
static int		test_parse_errors(int argc, char **argv);
static void		print_scene_brief(t_scene scene);

int	main(int argc, char **argv)
{
	test_parse_errors(argc, argv);
	return (0);
}

static int	test_parse_errors(int argc, char **argv)
{
	t_rt_mlx	app;

	rt_log_set_level(LOG_ALL);
	printf("\n-------------------------------------------------------------\n");
	printf("                     FILE PARSER TEST");
	printf("\n-------------------------------------------------------------\n");
	if (argc != 2)
		rt_error_msg(MSG_USAGE);
	ft_bzero(&app, sizeof(app));
	printf("\nTESTFILE: [%s]\n\n", ft_strrchr(argv[1], '/') + 1);
	if(parse_file(argv[1], &app.scene) != 0)
		return (1);
	print_scene_brief(app.scene);
	scene_clear(&app.scene);
	return (0);
}

static void	print_scene_brief(t_scene scene)
{
	printf("======================  PARSED SCENE  ======================\n");
	if (scene.has_ambient)
		printf("Ambient: ratio=%.2f color=(%f,%f,%f)\n",
			   scene.amb.ratio, scene.amb.color.x, scene.amb.color.x, scene.amb.color.z);
	if (scene.has_camera)
		printf("Camera:  pos(%.2f,%.2f,%.2f) dir(%.2f,%.2f,%.2f) fov=%.1f°\n",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z,
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z,
			   scene.cam.fov_deg);
	if (scene.has_light)
		printf("Light:   pos(%.2f,%.2f,%.2f) brightness=%.2f\n",
			   scene.light.pos.x, scene.light.pos.y, scene.light.pos.z,
			   scene.light.bright);
	printf("Objects: %d\n", scene.obj_count);
	t_obj *obj = scene.objs;
	while (obj)
	{
		printf("  - ");
		if (obj->type == OBJ_SPHERE)
			printf("Sphere:     center(%.2f,%.2f,%.2f) radius=%.2f\n",
				   obj->u.sp.center.x, obj->u.sp.center.y, obj->u.sp.center.z,
				   obj->u.sp.radius);
		else if (obj->type == OBJ_PLANE)
			printf("Plane:      point(%.2f,%.2f,%.2f) normal(%.2f,%.2f,%.2f)\n",
				   obj->u.pl.point.x, obj->u.pl.point.y, obj->u.pl.point.z,
				   obj->u.pl.normal.x, obj->u.pl.normal.y, obj->u.pl.normal.z);
		else if (obj->type == OBJ_CYLINDER)
			printf("Cylinder:   center(%.2f,%.2f,%.2f) radius=%.2f height=%.2f\n",
				   obj->u.cy.center.x, obj->u.cy.center.y, obj->u.cy.center.z,
				   obj->u.cy.radius, obj->u.cy.height);
		obj = obj->next;
	}
	printf("=============================================================\n");
}


static void	print_rt_file_content(t_scene scene)
{
	printf("┌─────────────────────────────────────────────────────┐\n");
	printf("│                PARSED SCENE INFORMATION             │\n");
	printf("└─────────────────────────────────────────────────────┘\n\n");
	
	// ==================== AMBIENT LIGHT ====================
	if (scene.has_ambient)
	{
		printf("【 AMBIENT LIGHT 】\n");
		printf("  ├─ Active:      YES\n");
		printf("  ├─ Ratio:       %.3f\n", scene.amb.ratio);
		printf("  └─ Color:       RGB(%f, %f, %f)\n\n", 
			   scene.amb.color.x, scene.amb.color.y, scene.amb.color.z);
	}
	else
	{
		printf("【 AMBIENT LIGHT 】\n");
		printf("  ├─ Active:      NO\n");
		printf("  └─ Using default values\n\n");
	}
	
	// ==================== CAMERA ====================
	if (scene.has_camera)
	{
		printf("【 CAMERA 】\n");
		printf("  ├─ Active:      YES\n");
		printf("  ├─ Position:    (%.3f, %.3f, %.3f)\n",
			   scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z);
		printf("  ├─ Direction:   (%.3f, %.3f, %.3f)\n",
			   scene.cam.dir.x, scene.cam.dir.y, scene.cam.dir.z);
		printf("  ├─ FOV:         %.2f°\n", scene.cam.fov_deg);
		printf("  └─ Normalized:  %s\n\n",
			   vec_len(scene.cam.dir) == 1.0 ? "YES" : "NO (WARNING)");
	}
	else
	{
		printf("【 CAMERA 】\n");
		printf("  ├─ Active:      NO\n");
		printf("  └─ ERROR: Camera is required!\n\n");
	}
	
	// ==================== LIGHT ====================
	if (scene.has_light)
	{
		printf("【 LIGHT 】\n");
		printf("  ├─ Position:    (%.3f, %.3f, %.3f)\n",
			   scene.light.pos.x, scene.light.pos.y, scene.light.pos.z);
		printf("  ├─ Brightness:  %.3f\n", scene.light.bright);
		printf("  └─ Color:       RGB(%f, %f, %f)\n\n",
			   scene.light.color.x, scene.light.color.y, scene.light.color.z);
	}
	else
	{
		printf("【 LIGHT 】\n");
		printf("  ├─ Active:      NO\n");
		printf("  └─ Scene will use ambient only\n\n");
	}
	
	// ==================== OBJECTS ====================
	printf("【 OBJECTS 】\n");
	printf("  ├─ Total count:  %d\n", scene.obj_count);
	
	if (scene.objs)
	{
		t_obj	*current = scene.objs;
		int		index = 1;
		
		while (current)
		{
			printf("  ├─ Object #%d:  ", index++);
			
			if (current->type == OBJ_SPHERE)
			{
				printf("SPHERE\n");
				printf("  │  ├─ Center:     (%.3f, %.3f, %.3f)\n",
					   current->u.sp.center.x,
					   current->u.sp.center.y,
					   current->u.sp.center.z);
				printf("  │  ├─ Radius:      %.3f\n", current->u.sp.radius);
				printf("  │  ├─ Diameter:    %.3f\n", current->u.sp.diameter);
				printf("  │  └─ Color:       RGB(%f, %f, %f)\n",
					   current->u.sp.color.x,
					   current->u.sp.color.y,
					   current->u.sp.color.z);
			}
			else if (current->type == OBJ_PLANE)
			{
				printf("PLANE\n");
				printf("  │  ├─ Point:       (%.3f, %.3f, %.3f)\n",
					   current->u.pl.point.x,
					   current->u.pl.point.y,
					   current->u.pl.point.z);
				printf("  │  ├─ Normal:      (%.3f, %.3f, %.3f)\n",
					   current->u.pl.normal.x,
					   current->u.pl.normal.y,
					   current->u.pl.normal.z);
				printf("  │  └─ Color:       RGB(%f, %f, %f)\n",
					   current->u.pl.color.x,
					   current->u.pl.color.y,
					   current->u.pl.color.z);
			}
			else if (current->type == OBJ_CYLINDER)
			{
				printf("CYLINDER\n");
				printf("  │  ├─ Center:      (%.3f, %.3f, %.3f)\n",
					   current->u.cy.center.x,
					   current->u.cy.center.y,
					   current->u.cy.center.z);
				printf("  │  ├─ Axis:        (%.3f, %.3f, %.3f)\n",
					   current->u.cy.axis.x,
					   current->u.cy.axis.y,
					   current->u.cy.axis.z);
				printf("  │  ├─ Radius:      %.3f\n", current->u.cy.radius);
				printf("  │  ├─ Height:      %.3f\n", current->u.cy.height);
				printf("  │  └─ Color:       RGB(%f, %f, %f)\n",
					   current->u.cy.color.x,
					   current->u.cy.color.y,
					   current->u.cy.color.z);
			}
			
			if (current->next)
				printf("  │\n");
			current = current->next;
		}
		printf("  └─ End of objects list\n\n");
	}
	else
	{
		printf("  └─ No objects in scene\n\n");
	}
	
	// ==================== SCENE SUMMARY ====================
	printf("【 SCENE SUMMARY 】\n");
	printf("  ├─ Ambient:      %s\n", scene.has_ambient ? "YES" : "NO");
	printf("  ├─ Camera:       %s\n", scene.has_camera ? "YES" : "NO");
	printf("  ├─ Light:        %s\n", scene.has_light ? "YES" : "NO");
	printf("  ├─ Objects:      %d\n", scene.obj_count);
	printf("  └─ Scene status: %s\n",
		   (scene.has_camera && scene.obj_count > 0) ? "VALID" : "INVALID");
	
	printf("\n┌─────────────────────────────────────────────────────┐\n");
	printf("│                   END OF REPORT                     │\n");
	printf("└─────────────────────────────────────────────────────┘\n");
}