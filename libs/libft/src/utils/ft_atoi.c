/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:03:16 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/20 21:01:23 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(int c);
static int	determine_sign(const char **str);
static int	convert_str_to_nbr(const char *str, int sign);

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	while (ft_iswhitespace(*nptr))
		nptr++;
	sign = determine_sign(&nptr);
	result = convert_str_to_nbr(nptr, sign);
	return (result);
}

static int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static int	determine_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static int	convert_str_to_nbr(const char *str, int sign)
{
	int	nbr;
	int	next_digit;

	nbr = 0;
	while (ft_isdigit(*str))
	{
		next_digit = *str - '0';
		nbr = nbr * 10 + next_digit;
		str++;
	}
	return (nbr * sign);
}
