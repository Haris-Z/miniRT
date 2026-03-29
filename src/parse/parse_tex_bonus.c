/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:19:09 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 20:13:56 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "rt_error.h"
#include "parse.h"

static int	read_header(int fd, char ***header, int *len)
{
	char			head[32];
	int				bytes;
	const size_t	spaces = 4;

	ft_bzero(head, sizeof(head));
	bytes = read(fd, &head, sizeof(head) - 1);
	if (bytes < 1)
		return (RT_ERR_TEX);
	*header = ft_split_ws(head);
	if (!*header)
		return (RT_ERR_MALLOC);
	*len = bytes - (ft_strlen((*header)[0])
			+ ft_strlen((*header)[1])
			+ ft_strlen((*header)[2]) + ft_strlen((*header)[3]) + spaces);
	return (0);
}

static int	load_tex(int fd, t_tex *out, char *tex, int read_pixels)
{
	int	read_bites;

	ft_memcpy(out->ptr, tex, read_pixels);
	read_bites = read(fd, out->ptr + read_pixels,
			(out->w * out->h * 3) - read_pixels);
	if (read_bites < (out->w * out->h * 3) - read_pixels)
		return (1);
	return (0);
}

// static bool	tok_count(char **tok, int expected)
// {
// 	int	n;
// 
// 	n = 0;
// 	while (tok && tok[n])
// 		n++;
// 	if (n != expected)
// 		return (false);
// 	return (true);
// }
// check invalid format with tok_count?
int	parse_tex(const char *t, t_tex *out)
{
	int			fd;
	char		**head;
	int			err;
	char		buf[512];
	int			s;

	buf[0] = '\0';
	ft_strlcat(buf, "textures/", sizeof buf);
	ft_strlcat(buf, t, sizeof(buf));
	head = NULL;
	fd = open(buf, O_RDONLY);
	if (fd < 0)
		return (RT_ERR_TEX);
	err = read_header(fd, &head, &s);
	if (err != 0)
		return (close(fd), err);
	out->w = ft_atoi(head[1]);
	out->h = ft_atoi(head[2]);
	out->color_depth = ft_atoi(head[3]);
	out->ptr = malloc(out->w * out->h * 3);
	if (!out->ptr)
		return (free_array(head), close(fd), RT_ERR_MALLOC);
	if (load_tex(fd, out, head[4], s) != 0)
		return (free(out->ptr), free_array(head), RT_ERR_TEX);
	return (free_array(head), close(fd), 0);
}
