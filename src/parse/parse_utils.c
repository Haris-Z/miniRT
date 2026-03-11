/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:11:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 23:28:01 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "libft.h"
#include "limits.h"

static int	validate_rgb(const char *s, int *out);
static bool	tok_count(char **tok, int expected);

int	parse_vec3(const char *tok, t_vec3 *out)
{
	char	**p;

	if (!tok || !out)
		return (RT_ERR_ARG);
	p = ft_split(tok, ',');
	if (!p)
		return (RT_ERR_MALLOC);
	if (!tok_count(p, 3))
		return (free_array(p), RT_ERR_FORMAT);
	if (ft_strtod(p[0], &out->x) != 0)
		return (free_array(p), RT_ERR_BAD_FLOAT);
	if (ft_strtod(p[1], &out->y) != 0)
		return (free_array(p), RT_ERR_BAD_FLOAT);
	if (ft_strtod(p[2], &out->z) != 0)
		return (free_array(p), RT_ERR_BAD_FLOAT);
	free_array(p);
	return (0);
}

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
	//*out = rt_scale(*out, 1.0 / len);
	return (RT_SUCCESS);
}

int	parse_unit_vec(t_vec3 v)
{
	double	len;

	if ((v.x < -1.0 || v.x > 1.0)
		|| (v.y < -1.0 || v.y > 1.0)
		|| (v.z < -1.0 || v.z > 1.0))
		return (RT_ERR_URANGE);
	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < 1e-12)
		return (RT_ERR_UZERO);
	if (fabs(len - 1.0) > 1e-3)
		return (RT_ERR_UNORM);
	return (0);
}

int	parse_color_vec(const char *tok, t_color *out)
{
	char	**p;
	int		err;
	int		r;
	int		g;
	int		b;

	p = ft_split(tok, ',');
	if (!p)
		return (RT_ERR_MALLOC);
	if (tok_count(p, 3) == false)
		return (free_array(p), RT_ERR_FORMAT);
	err = validate_rgb(p[0], &r);
	if (err != RT_SUCCESS)
		return (free_array(p), err);
	err = validate_rgb(p[1], &g);
	if (err != RT_SUCCESS)
		return (free_array(p), err);
	err = validate_rgb(p[2], &b);
	if (err != RT_SUCCESS)
		return (free_array(p), err);
	*out = color_rgb(r, g, b);
	free_array(p);
	return (E_OK);
}

static int	validate_rgb(const char *s, int *out)
{
	int	color_val;

	if (ft_strtoi(s, &color_val))
		return (RT_ERR_BAD_INT);
	if (color_val < 0 || color_val > 255)
		return (RT_ERR_RANGE_COLOR);
	*out = color_val;
	return (0);
}

static bool	tok_count(char **tok, int expected)
{
	int	n;

	n = 0;
	while (tok && tok[n])
		n++;
	if (n != expected)
		return (false);
	return (true);
}
