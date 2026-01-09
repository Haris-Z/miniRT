/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:02:44 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 20:29:55 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include "rt_error.h"
#include "parser.h"
#include "scene.h"
#include "libft.h"

int	parse_ratio(const char *tok, double *out)
{
	double	r;

	if (parse_double(tok, &r) != 0) //rt_log_error("Invalid Ratio");
		return (1);//return (rt_error_msg("Invalid ratio for "));
	if (r < 0.0 || r > 1.0) // check ratio range
		return (1);//return (rt_error_msg("Ratio out of range [0..1] for"));
	*out = r;
	return (0);
}

// A 0.2 255,255,255
int	parse_ambient(t_scene *s, char **t)
{
	t_ambient	a;

	ft_bzero(&a, sizeof(a));
	if (!t[1] || !t[2] || t[3])
	{
		rt_error_msg("Ambient (A): expected 'A ratio R,G,B'");
		return (E_PARSE_TRAILING_GARBAGE);
	}
	if (parse_ratio(t[1], &a.ratio) != 0)
		return (rt_error_msg("Invalid ratio (range/bad double) for Ambient (A)"));
	if (parse_color_vec(t[2], &a.color) != 0)
	{
		rt_error_msg("Invalid RGB color for Ambient (A)");
		return (1);
	}
	if (scene_set_ambient(s, a) != 0)
	{
		rt_error_msg("Duplicate ambient lighting (A)");
		return (E_PARSE_DUPLICATE_AMBIENT);
	}
	return (0);
}
