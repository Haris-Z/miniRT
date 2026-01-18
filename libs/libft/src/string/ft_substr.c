/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:38:54 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/17 14:21:37 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	avail;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		len = 0;
	else
	{
		avail = s_len - (size_t)start;
		if (len > avail)
			len = avail;
	}
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	if (len > 0)
		ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

// char	*ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	size_t	s_len;
// 	size_t	avail;
// 	char	*substr;

// 	if (s == NULL)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if ((size_t)start >= s_len)
// 		len = 0;
// 	else if (start + len > s_len)
// 		len = s_len - start;
// 	substr = (char *)malloc(len + 1);
// 	if (substr == NULL)
// 		return (NULL);
// 	if (len > 0)
// 		ft_memcpy(substr, s + start, len);
// 	substr[len] = '\0';
// 	return (substr);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	s_len;
// 	char	*substr;

// 	if (s == NULL)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len)
// 		return (ft_strdup(""));
// 	if ((start + len) > s_len)
// 		len = s_len - start;
// 	substr = malloc(len + 1);
// 	if (substr == NULL)
// 		return (NULL);
// 	ft_strlcpy(substr, s + start, len + 1);
// 	return (substr);
// }
