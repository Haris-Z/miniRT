/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:16:40 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 12:11:33 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_ptr;
	size_t			i;

	if (n == 0)
		return ;
	s_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s_ptr[i] = 0;
		i++;
	}
}
