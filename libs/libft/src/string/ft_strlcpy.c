/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:39:34 by hazunic           #+#    #+#             */
/*   Updated: 2024/09/26 18:35:36 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_buf_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dst_buf_len = size - 1;
	i = 0;
	while (i < dst_buf_len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*
#include <stdio.h>
#include <bsd/string.h>
void	test_ft_strlcpy(void)
{
	char *src = "Hello, World!";
	char dst[6];
	size_t ret;

	ret = ft_strlcpy(NULL, src, sizeof(dst));
	printf("Testing ft_strlcpy:\n");
	printf("Return:\t\t%zu\n", ret);
	printf("Destination: %s\n", dst);
}
void	test_strlcpy(void)
{
	char *src2 = "Hello, World!";
	char dst2[6];
	size_t ret2;

	ret2 = strlcpy(dst2, src2, sizeof(dst2));
	printf("Testing strlcpy:\n");
	printf("Return:\t\t%zu\n", ret2);
	printf("Destination: %s\n", dst2);
}
//cc -Wall -Wextra -Werror ft_strlcpy.c
//ft_strlen.c -lbsd  && ./a.out | cat -e
int main(void)
{
	test_ft_strlcpy();
	printf("\n");
	test_strlcpy();
	return (0);
}
*/