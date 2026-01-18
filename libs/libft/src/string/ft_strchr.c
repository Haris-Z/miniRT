/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:13:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/17 14:38:36 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	first_occurence;
	size_t	i;

	first_occurence = (unsigned char )c;
	i = 0;
	while (s[i] != '\0' && (unsigned char )s[i] != first_occurence)
		i++;
	if ((unsigned char )s[i] == first_occurence)
		return ((char *)&s[i]);
	return (((void *)0));
}
