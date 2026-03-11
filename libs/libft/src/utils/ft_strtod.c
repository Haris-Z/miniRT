/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:22:36 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 21:24:43 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	parse_fraction(const char **p, double *val)
{
	double	frac;
	double	div;

	if (**p == '\0')
		return (0);
	if (**p == '.')
		(*p)++;
	if (!ft_isdigit((unsigned char)**p))
		return (1);
	frac = 0.0;
	div = 1.0;
	while (ft_isdigit((unsigned char)**p))
	{
		frac = frac * 10.0 + (double)(**p - '0');
		div *= 10.0;
		(*p)++;
	}
	*val += frac / div;
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
	if (!ft_isdigit((unsigned char)*p))
		return (1);
	val = 0.0;
	while (ft_isdigit((unsigned char)*p))
		val = val * 10.0 + (double)(*p++ - '0');
	if (parse_fraction(&p, &val) != 0)
		return (1);
	p = skip_ws(p);
	if (*p != '\0')
		return (1);
	*out = (double)sign * val;
	return (0);
}
