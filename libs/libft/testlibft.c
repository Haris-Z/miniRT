/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testlibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:42:39 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 19:12:05 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "inc/libft.h"
#include <fcntl.h>

// cc -Wall -Wextra -Werror testlibft.c libft.a -o testlibft
int	test_join(void);
int test_substr(void);
int test_trim(void);
int test_strndup(void);
int test_gnl(void);
int test_gnl2(void);

int	main(void)
{
	//char buf[10];
	//char	*str = "hello";
	//ft_memcpy(buf, str, 6);
	//printf("buf: %s | len %zu\n", buf, ft_strlen(buf));

	//test_join();
	//test_substr();
	//test_trim();
	//test_strndup();
	test_gnl();
	//test_gnl2();
	return (0);
}

void *__f(unsigned int i, char *s)
{
	while (*s)
	{	
		*s = (unsigned char )i;
		s++;
	}
	return (NULL);
}

int	test_join(void)
{
	char const	*s1 = "Hello";
	char const	*s2 = "a";
	char		*j_str;
	

	j_str = ft_strjoin(s1, s2);
	if (j_str == NULL)
	{
		printf("ft_strjoin failed.\n");
		return (1);
	}
	else
		printf("s1: %zu \ns2: %zu\nj_str: %zu\ncombined string:\n%s\n",ft_strlen(s1), ft_strlen(s2), ft_strlen(j_str), j_str);
	ft_striteri(j_str, __f('_', j_str));
	printf("j-str:%s\n", j_str);
	free(j_str);
	return (0);
}

int test_substr(void)
{
	char const		*s = "Hello this is a tes in this string.";
	unsigned int	start;
	size_t			len;
	char 			*substr;

	start = 30;
	len = 5; // s + 5 or so also?
	substr = ft_substr(s, start, len);
	printf("length of s:\t%zu\n", ft_strlen(s));
	printf("parameters:\nstart:\t%d\nlen:\t%zu\n", start, len);
	if (substr == NULL)
		printf("alloc fail");
	else
		printf("substr: %s\n", substr);
	printf("length of subst %zu\n", ft_strlen(substr));
	free(substr);
	return (0);
}

int test_trim(void)
{
	printf("\n\ntrimtest:\n");
	char const		*s = "Hello this is a test in this string.";
	char 			*substr;

	printf("length of s:\t%zu\n", ft_strlen(s));
	substr = ft_strtrim(s, "t ");
	if (substr == NULL)
		printf("alloc fail");
	else
		printf("%s\n", substr);
	printf("length of subst %zu\n", ft_strlen(substr));
	free(substr);
	return (0);
}

int test_strndup(void)
{
	printf("\n\ndup_test:\n");
	char const		*s = "Hello this is a test in this string.";
	char 			*substr;

	size_t len = ft_strlen(s);
	printf("length of s:\t%zu\n", len);
	substr = ft_strndup(s, len + 5);
	if (substr == NULL)
		printf("alloc fail");
	else
		printf("%s\n", substr);
	printf("length of subst %zu\n", ft_strlen(substr));
	free(substr);
	return (0);
}
int test_gnl(void)
{
	printf("\n\ntest_gnl\n\n");
	//int fd = open("test_gnl.txt", O_RDONLY);
	//if (fd < 0)
	//	return (perror("open failed"), 1);

	char *line;
	int i = 0;
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		i++;
		printf("[%d]:%s",i, line);
		
		free(line);
	}
	//close(fd);
	return (0);
}

int test_gnl2(void)
{

	printf("\n\ntest_gnl -- 2\n\n");
	int fd = open("test_gnl.txt", O_RDONLY);
	if (fd < 0)
		return (perror("open failed"), 1);

	char *line;
	int i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d]:%s",i, line);
		if (i == 2)
			close(fd);
		i++;
		free(line);
	}
	close(fd);
	return (0);
}