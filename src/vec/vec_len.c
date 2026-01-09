/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:27:34 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 12:33:32 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

double	vec_len2(t_vec3 v)
{
	return (vec_dot(v, v));
}

double	vec_len(t_vec3 v)
{
	return (sqrt(vec_len2(v)));
}