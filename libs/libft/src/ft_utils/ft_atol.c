/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:20:14 by hazunic           #+#    #+#             */
/*   Updated: 2025/06/12 02:30:51 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static long	determine_sign(const char **str)
{
	long	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static long	convert_str_to_nbr(const char *str, long sign)
{
	long	nbr;
	long	next_digit;

	nbr = 0;
	while (ft_isdigit(*str))
	{
		next_digit = *str - '0';
		nbr = nbr * 10 + next_digit;
		str++;
	}
	return (nbr * sign);
}

long	ft_atol(const char *nptr)
{
	long	sign;
	long	result;

	while (ft_iswhitespace(*nptr))
		nptr++;
	sign = determine_sign(&nptr);
	result = convert_str_to_nbr(nptr, sign);
	return (result);
}
