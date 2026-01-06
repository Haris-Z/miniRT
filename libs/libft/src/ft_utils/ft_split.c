/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:17:25 by hazunic           #+#    #+#             */
/*   Updated: 2025/06/12 03:13:27 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split(char **arr, size_t i)
{
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static const char	*skip_delimiters(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (&s[i]);
}

static size_t	get_wordcount(const char *s, char c)
{
	size_t	word_count;

	word_count = 0;
	while (*s != '\0')
	{
		s = skip_delimiters(s, c);
		if (*s != '\0')
		{
			word_count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (word_count);
}

static char	**get_word_list(const char *s, char **word_list, char c)
{
	size_t	i;
	char	*next_delim_pos;
	size_t	sub_len;

	i = 0;
	while (*s != '\0')
	{
		s = skip_delimiters(s, c);
		if (*s == '\0')
			break ;
		next_delim_pos = ft_strchr(s, c);
		if (next_delim_pos == NULL)
			next_delim_pos = ft_strchr(s, '\0');
		sub_len = next_delim_pos - s;
		word_list[i] = ft_substr(s, 0, sub_len);
		if (word_list[i] == NULL)
		{
			free_split(word_list, i);
			return (NULL);
		}
		i++;
		s = next_delim_pos;
	}
	word_list[i] = NULL;
	return (word_list);
}

char	**ft_split(const char *s, char c)
{
	char	**word_list;
	size_t	word_count;

	if (s == NULL)
		return (NULL);
	word_count = get_wordcount(s, c);
	word_list = malloc((word_count + 1) * sizeof(char *));
	if (word_list == NULL)
		return (NULL);
	if (get_word_list(s, word_list, c) == NULL)
		return (NULL);
	return (word_list);
}

/*
#include <stdio.h>
int main(void)
{
	//const char	*s = "";
	const char	*s = "a";
	char		c = ' ';
	char **list = ft_split(s, c);
	int i;
	
	if (*list == NULL)
		printf("s is empty: %s\n", s);

	i  = 0;
	while (list[i] != NULL)
	{
		printf("element[%d]:%s\n", i, list[i]);
		i++;
	}
	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (0);
}
*/
