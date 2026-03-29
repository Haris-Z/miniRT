/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:48:09 by agara             #+#    #+#             */
/*   Updated: 2026/03/29 18:37:54 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

int	get_tex_index(t_vec3 surface_normal, t_tex tex)
{
	double	w;
	double	h;

	w = ((atan2(surface_normal.x, surface_normal.y) / (2.0 * PI)) + 0.5);
	h = (acos(surface_normal.z) / PI);
	w *= tex.w;
	h *= tex.h;
	if (h >= tex.h)
		h--;
	return (((int)h * tex.w + (int)w) * 3);
}
