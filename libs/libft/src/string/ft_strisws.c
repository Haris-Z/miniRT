/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:25:57 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 14:27:49 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stris_ws(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace((unsigned char)s[i]))
			return (1);
		i++;
	}
	return (0);
}
