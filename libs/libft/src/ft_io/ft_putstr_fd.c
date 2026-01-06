/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:52:49 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 12:40:42 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* note: re-implement to remove dependecy on ft_strlen */
void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return ;
	len = ft_strlen(s);
	write (fd, s, len);
}
