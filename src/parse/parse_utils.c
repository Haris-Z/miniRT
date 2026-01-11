/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:11:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/11 09:08:06 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "color.h"
#include "vec.h"
#include "parser.h"
#include "rt_error.h"
#include "libft.h"

static int	parse_next_token(char *dst, int dstsize, const char *src, int start, int end)
{
	int	i;

	i = 0;
	while (start + i < end && i < dstsize - 1)
	{
		dst[i] = src[start + i];
		i++;
	}
	dst[i] = '\0';
	return (i > 0);
}

static int	split3(const char *s, int *a, int *b)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	*a = -1;
	*b = -1;
	if (!s || !*s)
		return (0);
	while (s && s[i])
	{
		if (s[i] == ',')
		{
			if (c == 0)
				*a = i;
			else if (c == 1)
				*b = i;
			c++;
		}
		i++;
	}
	if (c != 2 || *a <= 0 || *b <= *a + 1)
		return (0);
	if (s[i - 1] == ',')
		return (0);
	return (1);
}

// re-implement - make more tests
int	parse_vec3(const char *tok, t_vec3 *out)
{
	int		c1;
	int		c2;
	double	x;
	double	y;
	double	z;
	char	tmp[128];

	if (!tok || !split3(tok, &c1, &c2))
	{
		//rt_error_msg("Invalid vec3 for ");
		return (1);
	}
	if (!parse_next_token(tmp, 128, tok, 0, c1) || parse_double(tmp, &x))
	{
		//rt_error_msg("Invalid vec3 for ");
		return (1);
	}
	if (!parse_next_token(tmp, 128, tok, c1 + 1, c2) || parse_double(tmp, &y))
	{
		//rt_error_msg("Invalid vec3 for ");
		return (1);
	}
	if (!parse_next_token(tmp, 128, tok, c2 + 1, (int)ft_strlen(tok)) || parse_double(tmp, &z))
	{
		//rt_error_msg("Invalid vec3 for ");
		return (1);
	}
	*out = vec3(x, y, z);
	return (0);
}

int	parse_color_vec(const char *tok, t_color *out)
{
	int		c1;
	int		c2;
	int		r;
	int		g;
	int		b;
	char	tmp[64];

	if (!tok || !split3(tok, &c1, &c2))
		return (rt_error_msg("Invalid RGB token"));
	if (!parse_next_token(tmp, (int)sizeof(tmp), tok, 0, c1)
		|| parse_int(tmp, &r) || r < 0 || r > 255)
		return (rt_error_msg("RGB out of range for (r)"));
	if (!parse_next_token(tmp, (int)sizeof(tmp), tok, c1 + 1, c2)
		|| parse_int(tmp, &g) || g < 0 || g > 255)
		return (rt_error_msg("RGB out of range for (g)"));
	if (!parse_next_token(tmp, (int)sizeof(tmp), tok, c2 + 1, (int)ft_strlen(tok))
		|| parse_int(tmp, &b) || b < 0 || b > 255)
		return (rt_error_msg("RGB out of range for (b)"));
	*out = color_rgb(r, g, b);
	return (0);
}
