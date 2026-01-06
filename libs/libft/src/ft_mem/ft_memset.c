/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:16:31 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 13:03:45 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_ptr;

	if (n == 0)
		return (s);
	s_ptr = (unsigned char *)s;
	while (n > 0)
	{
		*s_ptr = (unsigned char )c;
		s_ptr++;
		n--;
	}
	return (s);
}
