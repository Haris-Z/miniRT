/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:22:36 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 00:07:36 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "libft.h"

static const char	*skip_ws(const char *s)
{
	while (*s && ft_isspace((unsigned char)*s))
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

static int	parse_int_part(const char **p, double *val)
{
	int	digit;

	*val = 0.0;
	if (!ft_isdigit((unsigned char)**p))
		return (1);
	while (ft_isdigit((unsigned char)**p))
	{
		digit = **p - '0';
		if (*val > (DBL_MAX - (double)digit) / 10.0)
			return (1);
		*val = *val * 10.0 + (double)digit;
		(*p)++;
	}
	return (0);
}

static int	parse_frac_part(const char **p, double *val)
{
	double	place;
	int		digit;

	if (**p == '\0')
		return (0);
	if (**p != '.')
		return (0);
	(*p)++;
	if (!ft_isdigit((unsigned char)**p))
		return (1);
	place = 0.1;
	while (ft_isdigit((unsigned char)**p))
	{
		digit = **p - '0';
		*val += (double)digit * place;
		place *= 0.1;
		(*p)++;
	}
	return (0);
}

int	ft_strtod(const char *s, double *out)
{
	const char	*p;
	double		val;
	int			sign;

	if (!s || !out)
		return (1);
	p = skip_ws(s);
	sign = parse_sign(&p);
	if (parse_int_part(&p, &val) != 0)
		return (1);
	if (parse_frac_part(&p, &val) != 0)
		return (1);
	p = skip_ws(p);
	if (*p != '\0')
		return (1);
	val *= (double)sign;
	if (!isfinite(val))
		return (1);
	*out = val;
	return (0);
}
