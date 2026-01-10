/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/10 13:02:05 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rt_error.h"
#include "scene.h"
#include "parser.h"
#include "libft.h"
#include "trace_log.h"

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

static int	parse_lines(t_scene *s, char **t)
{
	if (!t[0])
		return (0);
	if (t[0][0] == '\n')
		return (0);
	if (t[0][0] == 'A' && t[0][1] == '\0')
		return (parse_ambient(s, t));
	if (t[0][0] == 'C' && t[0][1] == '\0')
		return (parse_camera(s, t));
	if (t[0][0] == 'L' && t[0][1] == '\0')
		return (parse_light(s, t));
	if (t[0][0] == 's' && t[0][1] == 'p' && t[0][2] == '\0')
		return (parse_sphere(s, t));
	// if (t[0][0] == 'p' && t[0][1] == 'l' && t[0][2] == '\0')
	// 	return (parse_plane(s, t));
	// if (t[0][0] == 'c' && t[0][1] == 'y' && t[0][2] == '\0')
	// 	return (parse_cylinder(s, t));
	TRACELOG(LOG_WARNING, "parse_lines() -> t[0]=%s", t[0]);
	return (E_PARSE_UNKNOWN_ID);
}

static int	validate_scene(t_scene *s)
{
	if (!s->has_ambient)
	{
		rt_error_msg("missing ambient light (A)");
		return (1);
	}
	if (!s->has_camera)
	{
		rt_error_msg("missing cam (C)");
		return (1);
	}
	if (!s->has_light)
	{
		rt_error_msg("missing light (L)");
		return (1);
	}
	return (0);
}

// add simpler file reading - remove gnl
int	parse_file(const char *path, t_scene *s)
{
	int			fd;
	char		*line;
	char		**toks;
	int			ln;
	t_eflag		e;
	int			any_tokens;

	if (!has_rt_ext(path))
		return (rt_log_error(E_PARSE_MISSING_TOKEN, "Scene file must have .rt extension", 0, NULL));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (rt_log_error(E_SYS, NULL, -1, NULL));
	ln = 0;
	any_tokens = 0;
	line = get_next_line(fd);
	TRACELOG(LOG_TRACE, "line=%s", line);
	while (line)
	{
		ln++;
		toks = ft_split(line, ' ');
		// int i = 0;
		// while (toks[i])
		// {
		// 	TRACELOG(LOG_INFO, "line=%s", toks[i]);
		// 	i++;
		// }
		free(line);
		if (!toks)
		{
			close(fd);
			scene_clear(s);
			return(rt_error_msg(strerror(errno)));
		}
		if (toks[0])
			any_tokens = 1;
		e = parse_lines(s, toks);
		free_array(toks);
		if (e != E_OK)
		{
			close(fd);
			scene_clear(s);
			return (rt_log_error(e, NULL, ln, NULL));
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (!any_tokens)
	{
		scene_clear(s);
		return (rt_error_msg("parse_file(): any tokens=0"));
	}
	e = validate_scene(s);
	if (e != E_OK)
	{
		scene_clear(s);
		return(rt_log_error(e, NULL, ln, NULL));
	}
	return (0);
}
