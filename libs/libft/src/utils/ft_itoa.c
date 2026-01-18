/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:30:08 by hazunic           #+#    #+#             */
/*   Updated: 2024/10/01 15:39:23 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (len + 1);
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	int_to_str(char *str, int n, int len)
{
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*number_str;
	int		len;

	if (n == INT_MIN)
	{
		number_str = malloc(12);
		if (number_str == NULL)
			return (NULL);
		ft_strlcpy(number_str, "-2147483648", 12);
		return (number_str);
	}
	len = get_number_len(n);
	number_str = malloc(len + 1);
	if (number_str == NULL)
		return (NULL);
	number_str[len] = '\0';
	int_to_str(number_str, n, len);
	return (number_str);
}
/*
#include <stdio.h>
int	main(void)
{

	//char *str = ft_itoa(-2147483648);
	char *str = ft_itoa(100);
	printf("ft_itoa:\t%s\n", str);

	return (0);
}
*/