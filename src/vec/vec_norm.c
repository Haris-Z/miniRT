/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:07:32 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/11 11:12:06 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

t_vec3	vec_norm(t_vec3 v)
{
	double	len;

	len = vec_len(v);
	if (len < 1e-12)
		return (vec3(0.0, 0.0, 0.0));
	return (vec_scale(v, 1.0 / len));
}
