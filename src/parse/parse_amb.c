/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:02:44 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:46:38 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "libft.h"

int	parse_ratio(const char *tok, double *out)
{
	double	r;

	if (parse_double(tok, &r) != 0)
		return (E_PARSE_BAD_RATIO);
	if (r < 0.0 || r > 1.0)
		return (E_PARSE_BAD_RATIO);
	*out = r;
	return (0);
}

int	parse_ambient(t_scene *s, char **t)
{
	t_ambient	a;

	ft_bzero(&a, sizeof(a));
	if (!t[1] || !t[2] || t[3])
		return (E_PARSE_FORMAT_A);
	if (parse_double(t[1], &a.ratio) != 0)
		return (E_PARSE_BAD_RATIO);
	if (a.ratio < 0.0 || a.ratio > 1.0)
		return (E_PARSE_BAD_RATIO);
	if (parse_color_vec(t[2], &a.color) != 0)
		return (E_PARSE_BAD_COLOR);
	a.rgb = color_to_int(a.color);
	if (scene_set_ambient(s, a) != 0)
		return (E_PARSE_DUPLICATE_A);
	return (0);
}
