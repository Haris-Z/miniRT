/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:53:27 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 14:56:02 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include "rt_error.h"
#include "scene.h"
#include "parser.h"
#include "libft.h"

// LIGHT
// id	Pos			Brightness	Colors
// L	-40,0,30	0.7 		255,255,255
int	parse_light(t_scene *s, char **t)
{
	t_light	light;

	ft_bzero(&light, sizeof(light));
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (rt_error_msg("Light (L): expected 'L x,y,z ratio R,G,B'"));
	if (parse_vec3(t[1], &light.pos) != 0)
		return(rt_error_msg("Invalid vec for Position Light"));
	if (parse_ratio(t[2], &light.bright) != 0)
		return (rt_error_msg("Invalid Brightness ratio (range/bad double) for Light (L)"));
	if (parse_color_vec(t[3], &light.color) != 0)
		return (1);
	if (scene_set_light(s, light))
		return (rt_error_msg("Duplicate L"));
	return (0);
}
















// static char *next_token(char **p)
// {
// 	char	*s;
// 	char	*b;
// 	s = *p;
// 	while (*s == ' ' || *s == '\t')
// 		s++;
// 	if (!*s)
// 	{
// 		*p = s;
// 		return (NULL);
// 	}
// 	b = s;
// 	while(*s && *s != ' ' && *s != '\t')
// 		s++;
// 	if (*s)
// 	{
// 		*s ='\0';
// 		s++;
// 	}
// 	*p = s;
// 	return (b);
// }