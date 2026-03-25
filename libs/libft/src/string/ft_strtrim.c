/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:02 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 12:49:42 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ltrim rtrim*/

static int	find_start_index(const char *s1, const char *set)
{
	int	start;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	return (start);
}

static int	find_end_index(const char *s1, const char *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (end >= 0 && ft_strrchr(set, s1[end]) != NULL)
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	start = find_start_index(s1, set);
	end = find_end_index(s1, set);
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}

/*
#include <stdio.h>
int main(void)
{
	char *s1 = "trimnottrimtrim";
	char *set = "trim";
	char *trimmed;

	trimmed = ft_strtrim(s1, set);
	printf("trimmed string:\t%s\noriginal string\t%s\n\n", trimmed, s1);

	char *s2 = "notrimnottrimtrimno";
	char *set2 = "trim";
	char *trimmed2;

	trimmed2 = ft_strtrim(s2, set2);
	printf("trimmed string:\t%s\noriginal string\t%s\n", trimmed2, s2);
	
	return (0);
}
*/