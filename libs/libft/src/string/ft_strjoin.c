/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:42:19 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 13:05:45 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	combined_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	combined_len = len_s1 + len_s2;
	joined_str = malloc(combined_len + 1);
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, s1, combined_len + 1);
	ft_strlcat(joined_str, s2, combined_len + 1);
	return (joined_str);
}
