/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:30:28 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 16:21:50 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			s_len;
	unsigned int	i;
	char			*modified_str;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	modified_str = malloc(s_len + 1);
	if (modified_str == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		modified_str[i] = f(i, s[i]);
		i++;
	}
	modified_str[i] = '\0';
	return (modified_str);
}
