/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 15:45:25 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "parse.h"
#include "libft.h"

static int	parse_line(t_scene *s, char *line, int line_num);
static int	validate_scene(t_scene *s);
static char	*sanitize_line(char *s);

int	load_scene(int fd, t_scene *s)
{
	char	*line;
	int		line_no;
	int		err;

	err = E_OK;
	line_no = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_no++;
		line = sanitize_line(line);
		if (!line)
			continue ;
		err = parse_line(s, line, line_no);
		free(line);
		if (err != E_OK)
			break ;
	}
	close(fd);
	if (err == E_OK)
		err = validate_scene(s);
	return (err);
}

static int	parse_line(t_scene *s, char *line, int line_num)
{
	char	**tokens;
	int		err;

	err = E_OK;
	tokens = ft_split_ws(line);
	if (!tokens)
		return (rt_error_msg(strerror(errno)));
	else if (tokens[0][0] == 'A' && tokens[0][1] == '\0')
		err = parse_ambient(s, tokens);
	else if (tokens[0][0] == 'C' && tokens[0][1] == '\0')
		err = parse_camera(s, tokens);
	else if (tokens[0][0] == 'L' && tokens[0][1] == '\0')
		err = parse_light(s, tokens);
	else if (tokens[0][0] == 's' && tokens[0][1] == 'p' && tokens[0][2] == '\0')
		err = parse_sphere(s, tokens);
	else if (tokens[0][0] == 'p' && tokens[0][1] == 'l' && tokens[0][2] == '\0')
		err = parse_plane(s, tokens);
	else if (tokens[0][0] == 'c' && tokens[0][1] == 'y' && tokens[0][2] == '\0')
		err = parse_cylinder(s, tokens);
	else
		err = RT_ERR_ID;
	if (err != E_OK)
		print_parse_err(line_num, tokens[0], err, line);
	free_array(tokens);
	return (err);
}

static int	validate_scene(t_scene *s)
{
	if (!s->has_ambient)
	{
		print_parse_err(0, C_RED"[A]"C_RESET, RT_ERR_MISSING, NULL);
		return (RT_ERR_MISSING);
	}
	if (!s->has_camera)
	{
		print_parse_err(0, C_RED"[C]"C_RESET, RT_ERR_MISSING, NULL);
		return (RT_ERR_MISSING);
	}
	if (!s->has_light)
	{
		print_parse_err(0, C_RED"[L]"C_RESET, RT_ERR_MISSING, NULL);
		return (RT_ERR_MISSING);
	}
	return (0);
}

static char	*sanitize_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		s[i] = '\0';
	i = 0;
	if (s[i] == '#')
		s[i] = '\0';
	i = ft_strlen(s);
	while (i > 0 && ft_isspace((unsigned char)s[i - 1]))
		s[--i] = '\0';
	if (!ft_stris_ws(s))
	{
		free(s);
		return (NULL);
	}
	return (s);
}
