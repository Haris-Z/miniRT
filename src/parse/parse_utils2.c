/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:11:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 16:18:20 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "parse.h"
#include "rt_error.h"
#include "libft.h"

int	parse_unit_vec3(const char *s, t_vec3 *out)
{
	double	len;
	int		err;

	err = parse_vec3(s, out);
	if (err != RT_SUCCESS)
		return (err);
	if (out->x < -1.0 || out->x > 1.0 || out->y < -1.0 || out->y > 1.0
		|| out->z < -1.0 || out->z > 1.0)
		return (RT_ERR_URANGE);
	len = vec_len(*out);
	if (len < 1e-12)
		return (RT_ERR_UZERO);
	if (fabs(len - 1.0) > 1e-3)
		return (RT_ERR_UNORM);
	return (RT_SUCCESS);
}
