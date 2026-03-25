/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 20:37:35 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 16:14:26 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char )*s1 - (unsigned char )*s2);
}

/*
#include <stdio.h>
#include <string.h>
void	testing_ft_strncmp(void)
{
	char	*s1 = "aellO";
	char	*s2 = "hello";
	int		result;

	result = ft_strncmp(s1, s2, 0);

	if (result == 0)
	{
		printf("strings are matching.\n");
		printf("result ft_strncmp:\t%d\n", result);
		printf("s1:\t%s\ns2:\t%s\n", s1, s2);

	}
	else if (result < 0)
	{
		printf("s1 is less than s2\n");
		printf("result ft_strncmp:\t%d\n", result);
		printf("s1:\t%s\ns2:\t%s\n", s1, s2);
	}
	else
	{
		printf("s1 is greater than s2\n");
		printf("result ft_strncmp:\t%d\n", result);
		printf("s1:\t%s\ns2:\t%s\n", s1, s2);
	}
}

void	testing_strncmp(void)
{
	char	*s1 = "aellO";
	char	*s2 = "hello";
	int		result;

	result = strncmp(s1, s2, 0);

	if (result == 0)
	{
		printf("strings are matching.\n");
		printf("result strncmp:\t\t%d\n", result);
		printf("s1:\t%s\ns2:\t%s\n", s1, s2);

	}
	else if (result < 0)
	{
		printf("s1 is less than s2\n");
		printf("result strncmp:\t\t%d\n", result);
		printf("s1:\t%s\ns2:\t%s\n", s1, s2);
	}
	else
	{
		printf("s1 is greater than s2\n");
		printf("result strncmp:\t\t%d\n", result);
		printf("s1:\t%s\ns2:\t%s\n", s1, s2);
	}
}

int	main(void)
{
	printf("test ft_strncmp:\n");
	testing_ft_strncmp();
	printf("\ntest strncmp:\n");
	testing_strncmp();
	return (0);
}
*/