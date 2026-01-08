/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:52:45 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 16:41:29 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

// # include "vec3.h"
// # include "color.h"

/**
 * @brief configs for the ambient light  from .rt file
 * 
 * add Description
 * 
 * @note
 *		file: minimal.rt example
 *
 *		|ID	|Ratio	|Color
 *		|A	|0.9 	|255,255,255
 *
 * @param ratio ambient lighting ratio in the range [0.0,1.0]
 * @param color R, G, B colors in the range [0-255]
 */
typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

/**
 * @brief configs for the camera from .rt file
 * 
 * add Description
 *
 * @note
 *		file: minimal.rt example
 *		|ID	|Position	|Direction	|FOV(in deg)
 *		|C	|0,-1,3		|0,0,-1		|70
 *
 *	@param pos		x, y, z coordinates of the viewpoint
 *	@param dir 		3D normalized orientation vector,
 *					in the range [-1,1] for each x, y, z axis
 *	@param fov_deg:	Horizontal field of view in degrees
 *					in the range [0,180]
 */
typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov_deg;
}	t_camera;

/**
 * @brief configs for the light
 * 
 * add Description
 * 
 * @note
 * 		file: minimal.rt example
 *		|ID	|Position	|Brightness	|Colors
 *		|L	|5,5,5		|0.8		|0,255,255
 *
 *	@param pos		x, y, z coordinates of the light point
 *	@param bright	the light brightness ratio
 *					in the range [0.0,1.0]
 *	@param color	(unused in mandatory part) R, G, B colors
 *					in the range [0-255]:
 */
typedef struct s_light
{
	t_vec3	pos;
	double	bright;
	t_color	color;
}	t_light;

/**
 * @brief 
 * 
 * @param
 * 
 * @todo add stuff
 */
typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}	t_sphere;

/**
 * @brief 
 * 
 * @param
 * 
 * @todo add stuff
 */
typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

/**
 * @brief 
 * 
 * @param
 * 
 * @todo add stuff
 */
typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
	t_color	color;
}	t_cylinder;

typedef enum e_obj_type
{
	OBJ_SPHERE = 1,
	OBJ_PLANE = 2,
	OBJ_CYLINDER = 3
}	t_obj_type;

/**
 * @brief 
 * 
 * @param
 * 
 * @todo add stuff
 */
typedef struct s_obj
{
	t_obj_type		type;
	union u_shape
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	}	u;
	struct s_obj	*next;
	sizet_t			obj_count; // for struct array for now using linked list
}	t_obj;

/**
 * @brief 
 * 
 * @param
 * 
 * @todo add stuff
 */
typedef struct s_scene /* info - sort fields by size for alignment */
{
	int			has_ambient;	// change to bool?
	int			has_camera;		// change to bool?
	int			has_light;		// change to bool? or return error code ?
	t_ambient	amb;
	t_camera	cam;
	t_light		light;
	t_obj		*objs;
	int			obj_count;
}	t_scene;

/* initialize and clear */

/**
 * @brief 
 * 
 * @param s 
 */
void	scene_init(t_scene *s);

/**
 * @brief 
 * 
 * @param s 
 */
void	scene_clear(t_scene *s);

/* initalize settings from parsing */

/**
 * @brief 
 * 
 * @param s 
 * @param a 
 * @return int 
 */
int		scene_set_ambient(t_scene *s, t_ambient a);

/**
 * @brief 
 * 
 * @param s 
 * @param c 
 * @return int 
 */
int		scene_set_camera(t_scene *s, t_camera c);

/**
 * @brief 
 * 
 * @param s 
 * @param l 
 * @return int 
 */
int		scene_set_light(t_scene *s, t_light l);

/* initialize objects for the scene fromg parsing*/

/**
 * @brief 
 * 
 * @param s 
 * @param sp 
 * @return int 
 */
int		scene_add_sphere(t_scene *s, t_sphere sp);

/**
 * @brief 
 * 
 * @param s 
 * @param pl 
 * @return int 
 */
int		scene_add_plane(t_scene *s, t_plane pl);

/**
 * @brief 
 * 
 * @param s 
 * @param cy 
 * @return int 
 */
int		scene_add_cylinder(t_scene *s, t_cylinder cy);

#endif // SCENE_H