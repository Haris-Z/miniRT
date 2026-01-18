/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:08:27 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 14:23:14 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "libft.h"

// move to libft - ft_strtoi
int	parse_int(const char *s, int *out)
{
	int		i;

	if (!s || !*s)
		return (1);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (1);
	*out = ft_atoi(s);
	return (0);
}

// refactor to atof -> add to libft
// move to libft - ft_strtod
int	parse_double(const char *s, double *out)
{
	double	val;
	double	frac;
	double	div;
	int		sign;
	int		i;

	if (!s || !*s)
		return (1);
	val = 0.0;
	frac = 0.0;
	div = 1.0;
	sign = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	if (!(ft_isdigit(s[i])))
		return (1);
	while (ft_isdigit(s[i]))
		val = val * 10.0 + (double)(s[i++] - '0');
	if (s[i] == '.')
	{
		i++;
		if (!(ft_isdigit(s[i])))
			return (1);
		while (ft_isdigit(s[i]))
		{
			frac = frac * 10.0 + (double)(s[i++] - '0');
			div *= 10.0;
		}
	}
	if (s[i] != '\0')
		return (1);
	*out = sign * (val + frac / div);
	return (0);
}
