/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:17:39 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 12:45:12 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	dup_size;
	char	*duplicate;

	if (src == NULL)
		return (NULL);
	dup_size = ft_strlen(src);
	duplicate = malloc(dup_size + 1);
	if (duplicate == NULL)
		return (NULL);
	ft_strlcpy(duplicate, src, dup_size + 1);
	return (duplicate);
}
