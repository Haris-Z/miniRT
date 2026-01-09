/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:49:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 18:15:04 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// # include "scene.h"

typedef struct s_scene t_scene;

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
int	parse_ratio(const char *tok, double *out);
int	parse_color_vec(const char *tok, t_color *out);

// CAMERA
// id	Direction	Orientation		FOV in deg
// C	-50,0,20 	1,0,0			70
int	parse_camera(t_scene *s, char **t);
int	parse_unit_vec(t_vec3 v);
int	parse_fov(const char *tok, double *out);

// LIGHT
// id	Pos			Brightness	Colors
// L	-40,0,30	0.7 		255,255,255
int	parse_light(t_scene *s, char **t);

// SPHERE
// id	center	diameter/radius		color
// sp	0,0,20				20		255,0,0
int	parse_sphere(t_scene *s, char **t);

#endif // PARSER_H