/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:19:56 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 14:37:01 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*update_buffer_for_next_line(char *stat_buf, char *line_end);
static char	*extract_from_buffer(char **stat_buf);
static int	read_from_fd_into_buffer(int fd, char **stat_buffer);
static char	*expand_buffer(char *stat_buf, char *read_buf);

/**
 * @details
 * - Allocates and returns the next line read from @p fd, including the
 * terminating newline character if one is encountered before EOF.
 * Successive calls will continue reading from where the previous
 * one stopped, using an internal static buffer.
 *
 * @param fd File descriptor to read from (must be open for reading).
 *
 * @return
 *  - A newly allocated string
 *    containing the next line (including '\n' if present).
 *  - NULL if there is nothing more to read or if an error occurs.
 *
 * @note Behavior is undefined if @p fd is negative, closed, or points to
 *       a non-readable stream.
 *       The caller is responsible for freeing the returned line.
 *
 * @par Example
 * @code
 * int fd = open("file.txt", O_RDONLY);
 * if (fd < 0)
 *     return (perror("open failed"), 1);
 *
 * char *line;
 * while ((line = get_next_line(fd)) != NULL)
 * {
 *     printf("%s", line);
 *     free(line);
 * }
 * close(fd);
 * @endcode
 *
 * @par Buffer flow diagram
 * @dot
 * digraph G {
 *     rankdir=LR;
 *     node [shape=box, fontname="monospace"];
 *
 *     fd      [label="fd\n(file descriptor)"];
 *     readf   [label="read_from_fd_into_buffer()"];
 *     stash   [label="stash\n(static buffer)"];
 *     extract [label="extract_from_buffer()"];
 *     line    [label="line\n(returned to caller)"];
 *     rem     [label="remainder\n(after '\\n')"];
 *
 *     fd -> readf [label="read()"];
 *     readf -> stash [label="append data"];
 *
 *     stash -> extract [label="search '\\n'"];
 *     extract -> line [label="prefix up to '\\n'"];
 *     extract -> rem  [label="suffix after '\\n'"];
 *     rem -> stash [label="stored for next call"];
 * }
 * @enddot
 */
char	*get_next_line(int fd)
{
	static char	*stat_buffer;
	int			read_count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_and_null(&stat_buffer));
	if (stat_buffer == NULL)
	{
		stat_buffer = (char *)malloc(1);
		if (stat_buffer == NULL)
			return (NULL);
		stat_buffer[0] = '\0';
	}
	read_count = read_from_fd_into_buffer(fd, &stat_buffer);
	if (read_count == READ_ERROR)
	{
		free_and_null(&stat_buffer);
		return (NULL);
	}
	return (extract_from_buffer(&stat_buffer));
}

/* OG */
static char	*update_buffer_for_next_line(char *stat_buf, char *line_end)
{
	size_t	remaining_len;
	char	*next_line;

	if (line_end == NULL || *line_end == '\0')
		return (free_and_null(&stat_buf));
	remaining_len = ft_strlen(line_end + 1);
	next_line = malloc(remaining_len + 1);
	if (next_line == NULL)
		return (free_and_null(&stat_buf));
	ft_memcpy(next_line, line_end + 1, remaining_len + 1);
	free_and_null(&stat_buf);
	return (next_line);
}

/*
 * Extracts the next line from the stash buffer.
 *
 * Searches *stat_buf for a newline. If found, allocates and returns everything
 * up to and including the newline, and updates *stat_buf to contain the
 * remaining data. If no newline exists, returns the last partial line and
 * clears the stash.
 *
 * stat_buf Address of the stash buffer.
 *
 * return Newly allocated line or NULL if the stash is empty.
 *
 * Caller must free the returned string.
 * Behavior is undefined if stat_buf or *stat_buf is NULL.
 *
 * stash = "hello\nworld"
 * char *line1 = extract_from_buffer(&stash); -> "hello\n"
 * char *line2 = extract_from_buffer(&stash); -> "world"
 * char *line3 = extract_from_buffer(&stash); -> NULL
 */
static char	*extract_from_buffer(char **stat_buf)
{
	char	*extracted_line;
	char	*line_end;
	size_t	line_len;

	if (stat_buf == NULL || !*stat_buf || **stat_buf == '\0')
		return (free_and_null(stat_buf));
	line_end = *stat_buf;
	line_len = 0;
	while (line_end[line_len] != '\0' && line_end[line_len] != '\n')
		line_len++;
	if (line_end[line_len] == '\n')
		line_len++;
	extracted_line = (char *)malloc(line_len + 1);
	if (extracted_line == NULL)
		return (free_and_null(stat_buf));
	ft_strlcpy(extracted_line, *stat_buf, line_len + 1);
	*stat_buf = update_buffer_for_next_line(*stat_buf, line_end + line_len - 1);
	return (extracted_line);
}

static char	*expand_buffer(char *stat_buf, char *read_buf)
{
	char	*combined_buf;

	if (stat_buf == NULL)
		return (NULL);
	combined_buf = ft_strjoin(stat_buf, read_buf);
	if (combined_buf == NULL)
	{
		free_and_null(&stat_buf);
		return (NULL);
	}
	free_and_null(&stat_buf);
	return (combined_buf);
}

/*
 * @brief Reads data from @p fd and appends it to the stash buffer.
 * @ingroup getline
 *
 * Reads up to BUFFER_SIZE bytes and appends them to @p *stash. Stops when
 * a newline is found, read() returns 0 (EOF), or a read error occurs.
 *
 * @param fd    File descriptor to read from.
 * @param stash Address of the dynamic stash buffer.
 *
 * @return
 *  - Number of bytes read (0–BUFFER_SIZE)  
 *  - 0 on EOF  
 *  - READ_ERROR (-1) on failure
 *
 * @note Behavior is undefined if @p stash or @p *stash is NULL.
 */
static int	read_from_fd_into_buffer(int fd, char **stat_buffer)
{
	char	read_buffer[BUFFER_SIZE + 1];
	ssize_t	read_size;

	while (ft_strchr(*stat_buffer, '\n') == NULL)
	{
		read_size = read(fd, read_buffer, BUFFER_SIZE);
		if (read_size == READ_ERROR)
		{
			free_and_null(stat_buffer);
			return (READ_ERROR);
		}
		if (read_size == EOF_REACHED)
			break ;
		read_buffer[read_size] = '\0';
		*stat_buffer = expand_buffer(*stat_buffer, read_buffer);
		if (*stat_buffer == NULL)
			return (READ_ERROR);
	}
	return (0);
}
