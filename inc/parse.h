/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:49:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 16:28:53 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define EXT_RT ".rt"
# define EXT_LEN 3

//# include "rt_error.h"
# include "mrt.h" // t_vec3, t_color, t_scene, s_ambient, s_camera, s_light
# include "textures.h"

typedef struct s_rt_file
{
	int			fd;
	int			sys_errno;
	int			err;
}	t_rt_file;

// load *.rt file
void	rt_load_file(int argc, const char *path, t_rt_file *out);
int		load_scene(int fd, t_scene *s);

// parse utils
int		parse_vec3(const char *tok, t_vec3 *out);
int		parse_unit_vec3(const char *s, t_vec3 *out);
int		parse_color_vec(const char *tok, t_color *out);
int		parse_fov(const char *tok, double *out);

// parse scene elements
int		parse_ambient(t_scene *s, char **t);
int		parse_camera(t_scene *s, char **t);
int		parse_light(t_scene *s, char **t);
int		parse_sphere(t_scene *s, char **t);
int		parse_plane(t_scene *s, char **t);
int		parse_cylinder(t_scene *s, char **t);

#endif // PARSER_H
