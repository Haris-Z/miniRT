/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:22:25 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 14:29:09 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	gnl_fill(t_file_handle *fh)
{
	ssize_t	bytes_read;

	bytes_read = read(fh->fd, fh->buf, BUFFER_SIZE);
	if (bytes_read >= 0)
	{
		fh->len = bytes_read;
		fh->pos = 0;
	}
	return (bytes_read);
}

ssize_t	gnl_next_nl(t_file_handle *fh)
{
	ssize_t	i;

	i = fh->pos;
	while (i < fh->len)
	{
		if (fh->buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_append(char *line, size_t *len, const char *src, size_t n)
{
	char	*new_line;
	size_t	i;

	new_line = NULL;
	i = 0;
	new_line = (char *)malloc(*len + n + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	while (i < *len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < *len + n)
	{
		new_line[i] = src[i - *len];
		i++;
	}
	new_line[*len + n] = '\0';
	free(line);
	*len += n;
	return (new_line);
}

int	gnl_prepare_buf(t_file_handle *fh, ssize_t *st)
{
	if (fh->pos >= fh->len)
		*st = gnl_fill(fh);
	if (*st <= 0)
		return (0);
	return (1);
}

int	gnl_consume_chunk(t_file_handle *fh, char **line, size_t *len)
{
	ssize_t	nl;
	size_t	take;

	nl = gnl_next_nl(fh);
	take = (size_t)(fh->len - fh->pos);
	if (nl >= 0)
		take = (size_t)(nl - fh->pos + 1);
	*line = gnl_append(*line, len, fh->buf + fh->pos, take);
	if (*line == NULL)
		return (-1);
	fh->pos += (ssize_t)take;
	if (nl >= 0)
		return (1);
	return (0);
}
