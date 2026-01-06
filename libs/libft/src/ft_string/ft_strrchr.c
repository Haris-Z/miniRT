/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:59 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 16:14:08 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* check if NUL found*/
char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurence;

	last_occurence = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char )c)
			last_occurence = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (last_occurence);
}
/*
#include <stdio.h>
#include <string.h>

void	testing_strrchr(void)
{
	char	*src = "hello worwld";
	//char	*src = NULL;
	char	*result;
	int		c = '\0'; 
	//int		c = 'w';

	result = strrchr(src, c);
	printf("testing strrchr:\n");
	if (*result == '\0')
	{
		printf("input string: %s\n", src);
		printf("found '\\0' at index %ld\n", result - src);
	}
	else
	{
		printf("input string: %s\n", src);
		printf("found %c at index %ld\n", c, result - src);
		printf("remaining string: %s\n", result);
	}
}

void	testing_ft_strrchr(void)
{
	char	*src = "hello worwld";
	//char	*src = NULL;
	char	*result;
	int		c = '\0'; 
	//int		c = 'w';

	result = ft_strrchr(src, c);
	printf("testing ft_strrchr:\n");
	if (*result == '\0')
	{
		printf("input string: %s\n", src);
		printf("found '\\0' at index %ld\n", result - src);
	}
	else
	{
		printf("input string: %s\n", src);
		printf("found %c at index %ld\n", c, result - src);
		printf("remaining string: %s\n", result);
	}
}

int	main(void)
{
	testing_ft_strrchr();
	printf("\n");
	testing_strrchr();
}
*/