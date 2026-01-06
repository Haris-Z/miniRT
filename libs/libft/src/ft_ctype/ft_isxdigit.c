/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:14:52 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 12:02:32 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isxdigit(int c)
{
	int	is_hex_lower;
	int	is_hex_upper;

	is_hex_lower = (c >= 'a' && c <= 'f');
	is_hex_upper = (c >= 'A' && c <= 'F');
	if (ft_isdigit(c) || is_hex_upper || is_hex_lower)
		return (1);
	return (0);
}
