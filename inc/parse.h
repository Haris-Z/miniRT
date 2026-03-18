/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:49:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 18:02:32 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define DFLT_OBJ_CAP 8
# define EXT_RT ".rt"
# define EXT_LEN 3

# include "rt_error.h"
# include "mrt.h" // t_vec3, t_color, t_scene, s_ambient, s_camera, s_light

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

// typedef struct s_parse_err
// {
// 	int			err;
// 	int			sys_errno;
// 	int			lineno;
// 	char		id[8];
// }	t_parse_err;

// typedef int	(*t_parse_fn)(t_scene *s, char **tok);
// 
// typedef struct s_parse_entry
// {
// 	const char	*id;
// 	t_parse_fn	parse_fn;
// }	t_parse_entry;

// t_parse_entry	*rt_find_entry(const char *id);

#endif // PARSER_H
