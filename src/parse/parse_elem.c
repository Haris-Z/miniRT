/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:02:44 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 19:52:27 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "libft.h"

static bool tok_count(char **tok, int expected)
{
	int	n;

	n = 0;
	while (tok && tok[n])
		n++;
	if (n != expected)
		return (false);
	return (true);
}

// int	parse_ratio(const char *tok, double *out)
// {
// 	double	r;
// 
// 	if (parse_double(tok, &r) != 0)
// 		return (E_PARSE_BAD_RATIO);
// 	if (r < 0.0 || r > 1.0)
// 		return (E_PARSE_BAD_RATIO);
// 	*out = r;
// 	return (0);
// }

// id	Ratio	r	g	b
// A	0.2 	255,255,255
int	parse_ambient(t_scene *s, char **t)
{
	t_ambient	a;
	int			err;

	ft_bzero(&a, sizeof(a));
	if (tok_count(t, 3) == false)
		return (RT_ERR_TOK);
	if (ft_strtod(t[1], &a.ratio) != 0)
		return (RT_ERR_BAD_FLOAT);
	if (a.ratio < 0.0 || a.ratio > 1.0)
		return (RT_ERR_BAD_RATIO);
	err = parse_color_vec(t[2], &a.color);
	if (err)
		return (err);
	if (scene_set_ambient(s, a) != 0)
		return (RT_ERR_DUP);
	return (E_OK);
}

int	parse_fov(const char *tok, double *out)
{
	int	fov;

	if (ft_strtoi(tok, &fov))
		return (RT_ERR_BAD_INT);
	if (fov < 0 || fov > 180)
		return (RT_ERR_RANGE_FOV);
	*out = fov;
	return (0);
}

// id	Direction	Orientation		FOV in deg
// C	-50,0,20 	1,0,0			70
int	parse_camera(t_scene *s, char **t)
{
	t_camera	cam;
	int			err;

	ft_bzero(&cam, sizeof(cam));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (RT_ERR_TOK);
	err = parse_vec3(t[1], &cam.pos);
	if (err != RT_SUCCESS)
		return (err);
	err = parse_unit_vec3(t[2], &cam.dir);
	if (err != RT_SUCCESS)
		return(err);
	err = parse_fov(t[3], &cam.fov_deg);
	if (err != RT_SUCCESS)
		return(err);
	if (scene_set_camera(s, cam) != 0)
		return (RT_ERR_DUP);
	return (0);
}

// LIGHT
// id	Pos			Brightness	Colors
// L	-40,0,30	0.7 		255,255,255
int	parse_light(t_scene *s, char **t)
{
	t_light	light;
	int		err;

	if (!t[1] || !t[2] || !t[3] || t[4])
		return (RT_ERR_FORMAT_LIGHT);
	err = parse_vec3(t[1], &light.pos);
	if (err != RT_SUCCESS)
		return(err);
	if (ft_strtod(t[2], &light.bright) != 0)
		return (RT_ERR_BAD_FLOAT);
	if (light.bright < 0.0 || light.bright > 1.0)
		return (RT_ERR_BAD_RATIO);
	err = parse_color_vec(t[3], &light.color);
	if (err != RT_SUCCESS)
		return (err);
	if (scene_set_light(s, light) != 0)
		return (RT_ERR_LIGHT_COUNT);
	return (0);
}


// int	parse_light(t_scene *s, char **t)
// {
// 	t_light	light[MAX_LIGHTS];
// 	int		err;
// 
// 	if (!t[1] || !t[2] || !t[3] || t[4])
// 		return (RT_ERR_FORMAT_LIGHT);
// 	err = parse_vec3(t[1], &light[s->light_count].pos);
// 	if (err != RT_SUCCESS)
// 		return(err);
// 	if (ft_strtod(t[2], &light[s->light_count].bright) != 0)
// 		return (RT_ERR_BAD_FLOAT);
// 	if (light[s->light_count].bright < 0.0 || light[s->light_count].bright > 1.0)
// 		return (RT_ERR_BAD_RATIO);
// 	err = parse_color_vec(t[3], &light[s->light_count].color);
// 	if (err != RT_SUCCESS)
// 		return (err);
// 	if (scene_set_light(s, light[s->light_count]) != 0)
// 		return (RT_ERR_DUP);
// 	return (0);
// }
