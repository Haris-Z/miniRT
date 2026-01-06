/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 12:44:57 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* test for returning NUL*/
char	*ft_strchr(const char *s, int c)
{
	char	*first_occurence;
	size_t	i;

	first_occurence = NULL;
	i = 0;
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char) c)
		first_occurence = (char *)&s[i];
	return (first_occurence);
}
