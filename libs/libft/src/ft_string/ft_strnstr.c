/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:03:05 by hazunic           #+#    #+#             */
/*   Updated: 2024/10/01 16:18:07 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (*little == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big != '\0' && little_len <= len)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>
//cc -Wall -Wextra -Werror ft_strnstr.c ft_strlen.c
//ft_strncmp.c -lbsd  && ./a.out | cat -e
void	test_ft_strnstr(void)
{
	const char	*big = "a";
	const char	*little = "a";
	char 		*result;

	result = ft_strnstr(big, little, 13);
	printf("testing ft_strnstr:\n");
	if (result == NULL)
		printf("substring not found\n");
	else
		printf("little: %s\nfound in big: %s\n", little, result);
}

void	test_strnstr(void)
{
	const char	*big = "Hello World";
	const char	*little = "World";
	char 		*result;

	result = strnstr(big, little, 0);
	printf("testing strnstr:\n");
	if (result == NULL)
		printf("substring not found\n");
	else
		printf("little: %s\nfound in big: %s\n", little, big);
}

int	main(void)
{
	test_ft_strnstr();
	test_strnstr();
	return (0);
}
*/