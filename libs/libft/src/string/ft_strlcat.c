/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:39:44 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 12:47:14 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	copy_len;
	size_t	i;

	dst_len = ft_strnlen(dst, size);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		return (size + src_len);
	copy_len = size - dst_len - 1;
	if (copy_len > src_len)
		copy_len = src_len;
	i = 0;
	while (i < copy_len)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*
#include <stdio.h>
#include <bsd/string.h>

void	test_strlcat(void)
{
	char	buf[20] = "hello ";
	char	str2[20] = "world.";//behaviour with 6 
	size_t	result;
	
	result = strlcat(buf, str2, sizeof(buf));
	printf("strlcat:\nbuf:\t%s\nresult:\t%zu\n", buf, result);
}

void	test_strlcat_null(void)
{
	char	*buf = NULL;
	char	*str2 = "world.";
	size_t	result;
	
	result = strlcat(buf, str2, 0);
	printf("strlcat:\nbuf:\t%s\nresult:\t%zu\n", buf, result);
}
void	test_ft_strlcat(void)
{
	char	buf[20] = "hello ";
	char	str2[7] = "world.";
	size_t	result;
	
	result = ft_strlcat(buf, str2, sizeof(buf));
	printf("ft_strlcat:\nbuf\t%s\nresult:\t%zu\n", buf, result);
}

void	test_ft_strlcat_null(void)
{
	char	*buf = NULL;
	//char buf[20] = "hello ";
	char	*str2 = "world.";
	size_t	result;
	
	result = ft_strlcat(buf, str2, 0);
	printf("ft_strlcat:\nbuf\t%s\nresult:\t%zu\n", buf, result);
}

int	main(void)
{
	test_strlcat();
	test_ft_strlcat();
	printf("\nTesting buf = NULL || size = 0\n");
	test_strlcat_null();
	test_ft_strlcat_null();
	return (0);
}
*/