/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:22:33 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/10 16:50:30 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_ws(const char *s)
{
	while (*s && ft_isspace((unsigned char )*s))
		s++;
	return (s);
}

static int	parse_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

static int	acc_add_digit(long long *acc, int sign, int d)
{
	*acc = (*acc) * 10 + d;
	if (sign == 1 && *acc > 2147483647LL)
		return (1);
	if (sign == -1 && *acc > 2147483648LL)
		return (1);
	return (0);
}

int	ft_strtoi(const char *s, int *out)
{
	const char	*p;
	long long	acc;
	int			sign;
	int			digits;

	if (!s || !out)
		return (1);
	p = skip_ws(s);
	sign = parse_sign(&p);
	acc = 0;
	digits = 0;
	while (*p && ft_isdigit((unsigned char)*p))
	{
		if (acc_add_digit(&acc, sign, *p - '0') != 0)
			return (1);
		digits++;
		p++;
	}
	p = skip_ws(p);
	if (digits == 0 || *p != '\0')
		return (1);
	*out = (int)(acc * sign);
	return (0);
}
