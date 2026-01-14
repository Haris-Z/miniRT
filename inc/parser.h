/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:49:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/13 19:11:56 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene.h"

typedef struct s_scene t_scene;

// add parse struct
// fd, ln, line, tok etc.

/**
 * @brief 
 * 
 * @param path 
 * @param s 
 * @return int 
 */
int	parse_file(const char *path, t_scene *s);

// utils
int	parse_vec3(const char *tok, t_vec3 *out);
int	parse_int(const char *s, int *out);
int	parse_double(const char *s, double *out);

// AMBIENT
// id	Ratio	r	g	b
// A	0.2 	255,255,255
int	parse_ambient(t_scene *s, char **t);
// int	parse_ambient(t_scene *s, char **t, int line_num);
int	parse_ratio(const char *tok, double *out);
int	parse_color_vec(const char *tok, t_color *out);

// CAMERA
// id	Direction	Orientation		FOV in deg
// C	-50,0,20 	1,0,0			70
int	parse_camera(t_scene *s, char **t);
// int	parse_camera(t_scene *s, char **t, int line_num);
int	parse_unit_vec(t_vec3 v);
int	parse_fov(const char *tok, double *out);

// LIGHT
// id	Pos			Brightness	Colors
// L	-40,0,30	0.7 		255,255,255
int	parse_light(t_scene *s, char **t);

// SPHERE
// id	center		diameter	color
// sp	0,0,20		20			255,0,0
int	parse_sphere(t_scene *s, char **t);

// PLANE
// id	point		normal		color
// pl	0,-2,0		0,1,0		200,200,200
int	parse_plane(t_scene *s, char **t);

// CYLINDER
// id	center		axis	diameter	height	color
// cy	2,0,0		0,1,0	1			3		0,0,255
int	parse_cylinder(t_scene *s, char **t);

#endif // PARSER_H