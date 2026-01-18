/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:22:52 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/17 13:32:56 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isblank(int c)
{
	unsigned char	cc;

	cc = (unsigned char )c;
	if (cc == ' ' || cc == '\t')
		return (1);
	return (0);
}
