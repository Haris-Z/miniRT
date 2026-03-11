/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:12:17 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 14:55:56 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	src_len;
	char	*duplicate;

	src_len = ft_strlen(src);
	if (n < src_len)
		src_len = n;
	duplicate = malloc(src_len + 1);
	if (duplicate == NULL)
		return (NULL);
	ft_strlcpy(duplicate, src, src_len + 1);
	return (duplicate);
}
