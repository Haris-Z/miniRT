/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:47:31 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "mrt.h"
#include "rt_error.h"
#include "libft.h"

// add simpler file reading - remove gnl
/*
	-[x] multiple spaces/tabs between fields
	-[x] blank lines
	-[x] any element order
	-[x] A	| ratio				| rgb
	-[x] C	| pos	| dir		| fov
	-[x] L	| pos	| bright	| rgb
	-[x] sp	| pos	| diameter	| rgb
	-[x] pl	| pos	| normal	| rgb
	-[x] cy	| pos	| axis		| diameter	| height	| rgb

	- validate
	-[x] ratios [0..1]
	-[x] FOV [0..180]
	-[x] colors [0..255]
	-[x] normals/orientation components in [-1..1] + length
	-[x] positive diameter/height
	-[x] only once of A/C/L
*/
/**
 * @brief
 * 
 */
static int	has_rt_ext(const char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (i < 3)
		return (0);
	if (s[i - 3] == '.' && s[i - 2] == 'r' && s[i - 1] == 't')
		return (1);
	return (0);
}

static int	parse_lines(t_scene *s, char *line, int line_num)
{
	char	**tokens;
	int		result;
	
	if (!line || line[0] == '\n' || line[0] == '#')
		return (0);
	tokens = ft_split(line, ' ');
	if(!tokens)
		return (rt_error_log(E_SYS, NULL, 0, NULL));
	result = 0;
	if (!tokens[0]) 
		result = E_FILE_EMPTY;
	else if (tokens[0][0] == 'A' && tokens[0][1] == '\0')
		result = parse_ambient(s, tokens);
	else if (tokens[0][0] == 'C' && tokens[0][1] == '\0')
		result = parse_camera(s, tokens);
	else if (tokens[0][0] == 'L' && tokens[0][1] == '\0')
		result = parse_light(s, tokens);
	else if (tokens[0][0] == 's' && tokens[0][1] == 'p' && tokens[0][2] == '\0')
		result = parse_sphere(s, tokens);
	else if (tokens[0][0] == 'p' && tokens[0][1] == 'l' && tokens[0][2] == '\0')
		result = parse_plane(s, tokens);
	else if (tokens[0][0] == 'c' && tokens[0][1] == 'y' && tokens[0][2] == '\0')
		result =  parse_cylinder(s, tokens);
	else
		result = E_PARSE_UNKNOWN_ID;
	if (result)
		rt_error_log(result, NULL, line_num, tokens[0]);
	free_array(tokens);
	return (result);
}

static int	validate_scene(t_scene *s)
{
	if (!s->has_ambient)
		rt_error_log(E_PARSE_MISSING_TOKEN, MSG_MISSING_A, 0, NULL);
	else if (!s->has_camera)
		rt_error_log(E_PARSE_MISSING_TOKEN, MSG_MISSING_C, 0, NULL);
	else if (!s->has_light)
		rt_error_log(E_PARSE_MISSING_TOKEN, MSG_MISSING_L, 0, NULL);
	else
		return (0);
	return (1);
}

static	int parse_open_file(const char *file_name, int *fd)
{
	
	if (!has_rt_ext(file_name))
	{
		rt_error_msg(MSG_FILE_EXT);
		return (E_FILE_EXT);
	}
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
	{
		rt_error_msg(strerror(errno));
		return (E_SYS);
	}
	return (0);
}

int	parse_file(const char *path, t_scene *s)
{
	int		fd;
	char	*line;
	int		line_no;
	int		err;

	if (parse_open_file(path, &fd) != 0)
		return (1);
	line_no = 0;
	line = get_next_line(fd);
	err = 0;
	while (line)
	{
		line_no++;
		if (err == 0)
			err = parse_lines(s, line, line_no); // verify if gnl is freed on only return
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (err != E_OK || validate_scene(s) != 0)
	{
		scene_clear(s);
		return (err);
	}
	return (0);
}
