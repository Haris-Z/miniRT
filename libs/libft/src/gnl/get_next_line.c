/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:19:56 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 14:28:57 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*gnl_read_line(t_file_handle *fh);

char	*get_next_line(int fd)
{
	static t_file_handle	fh;
	char					*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fh.fd != fd)
	{
		fh.fd = fd;
		fh.len = 0;
		fh.pos = 0;
	}
	line = gnl_read_line(&fh);
	return (line);
}

static char	*gnl_read_line(t_file_handle *fh)
{
	char	*line;
	size_t	len;
	ssize_t	st;
	int		done;

	line = NULL;
	len = 0;
	st = 1;
	while (1)
	{
		if (!gnl_prepare_buf(fh, &st))
			break ;
		done = gnl_consume_chunk(fh, &line, &len);
		if (done < 0)
			return (NULL);
		if (done > 0)
			return (line);
	}
	if (st < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
