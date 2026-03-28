/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:58:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/28 23:43:33 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // remove
#include "mrt.h"
#include "rt_error.h"
#include "libft.h"
#include <stdio.h> // remove

static int	parse_line(t_scene *s, char *line, int line_num);
static int	validate_scene(t_scene *s);
static char	*sanitize_line(char *s);

// filename for error
int	load_scene(int fd, t_scene *s)
{
	char	*line;
	int		line_no;
	int		err;

	line_no = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = sanitize_line(line);
		if (!line)
			continue ;
		err = parse_line(s, line, line_no++);
		if (err != E_OK)
		{
			free(line);
			break ;
		}
		free(line);
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

//else if () "too many lights"
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

// const t_parse_entry	*rt_find_entry(const char *id)
// {
// 	static const t_parse_entry	table[] = {
// 		{"A",  parse_ambient},
// 		{"C",  parse_camera},
// 		{"L",  parse_light},
// 		{"sp", parse_sphere},
// 		{"pl", parse_plane},
// 		{"cy", parse_cylinder},
// 		{NULL, NULL}
// 	};
// 	int	i;
// 
// 	i = 0;
// 	while (table[i].id)
// 	{
// 		if (ft_strncmp(table[i].id, id, ft_strlen(id)) == 0)
// 			return (&table[i]);
// 		i++;
// 	}
// 	return (NULL);
// }
