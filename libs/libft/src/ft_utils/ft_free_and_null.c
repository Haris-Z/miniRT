/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_null.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:21:15 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 19:56:59 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_and_null(char **ptr_to_free)
{
	if (ptr_to_free != NULL && *ptr_to_free != NULL)
	{
		free(*ptr_to_free);
		*ptr_to_free = NULL;
	}
	return (NULL);
}
