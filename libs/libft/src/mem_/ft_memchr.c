/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 20:45:36 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 12:48:41 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_ptr = (const unsigned char *)s;
	unsigned char		ch;

	ch = (unsigned char )c;
	while (n--)
	{
		if (*s_ptr == ch)
			return ((void *)s_ptr);
		s_ptr++;
	}
	return (NULL);
}
