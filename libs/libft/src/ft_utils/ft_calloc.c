/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:03:24 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 14:36:11 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h> /* SIZE_MAX*/
#include <stdlib.h> /* malloc */

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_ptr;
	size_t	total_size;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	total_size = nmemb * size;
	mem_ptr = malloc(total_size);
	if (mem_ptr == NULL)
		return (NULL);
	ft_bzero(mem_ptr, total_size);
	return (mem_ptr);
}
