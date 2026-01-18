/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:31:21 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/17 16:34:04 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

int	main(void)
{
	size_t len = ft_strlen("hello");
	printf("hello libft\n");
	printf("len: %lu\n", len);

	printf("\nTEST: get_next_line\n");
	char	*line;
	int		fd;

	fd = open("tests/lines.txt", O_RDONLY);
	line = get_next_line(fd);
	int i = 1;
	while(line != NULL)
	{
		printf("line %d: %s", i, line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}