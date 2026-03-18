/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:58:04 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 14:24:28 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif // BUFFER_SIZE

# include <unistd.h>
# include <stdlib.h>

typedef struct s_file_handle
{
	int		fd;
	char	buf[BUFFER_SIZE];
	ssize_t	len;
	ssize_t	pos;
}	t_file_handle;

char	*get_next_line(int fd);
ssize_t	gnl_fill(t_file_handle *fh);
ssize_t	gnl_next_nl(t_file_handle *fh);
char	*gnl_append(char *line, size_t *len, const char *src, size_t n);
int		gnl_prepare_buf(t_file_handle *fh, ssize_t *st);
int		gnl_consume_chunk(t_file_handle *fh, char **line, size_t *len);

#endif // GET_NEXT_LINE_H