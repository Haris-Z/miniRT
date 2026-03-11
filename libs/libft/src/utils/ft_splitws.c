/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:48:56 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/08 19:11:06 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s)
{
	size_t	n;
	int		in;

	n = 0;
	in = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && in == 0)
			n++;
		in = (!ft_isspace(*s));
		s++;
	}
	return (n);
}

static const char	*skip_ws(const char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (s);
}

static void	free_split_ws(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split_ws(const char *s)
{
	char	**arr;
	size_t	i;
	size_t	n;
	size_t	len;

	if (!s)
		return (NULL);
	n = count_words(s);
	arr = (char **)malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		s = skip_ws(s);
		len = 0;
		while (s[len] && !ft_isspace(s[len]))
			len++;
		arr[i] = ft_strndup(s, len);
		if (!arr[i])
			return (free_split_ws(arr), NULL);
		s += len;
	}
	arr[i] = NULL;
	return (arr);
}
