/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:17:16 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 12:50:49 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_ptr = (const unsigned char *)s1;
	const unsigned char	*s2_ptr = (const unsigned char *)s2;
	unsigned char		a;
	unsigned char		b;

	if (n == 0)
		return (0);
	while (n--)
	{
		a = *s1_ptr++;
		b = *s2_ptr++;
		if (a != b)
			return ((int)a - (int)b);
	}
	return (0);
}
