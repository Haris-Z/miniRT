/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:34:57 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 13:23:31 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
 * Implementation notes:
 * - If src < dst and the ranges overlap, copy backwards.
 * - Otherwise copy forwards.
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*s = (const unsigned char *)src;
	unsigned char		*d;
	size_t				i;

	if (dst == src || n == 0)
		return (dst);
	i = 0;
	d = (unsigned char *)dst;
	if (d > s && d < s + n)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
