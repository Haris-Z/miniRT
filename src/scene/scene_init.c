/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:50:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:47:59 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"

/**
 * @brief 
 * @param s 
 */
void	scene_init(t_scene *s)
{
	ft_bzero(s, sizeof(*s));
	s->objects_array = NULL;
	s->objects_cap = 0;
	s->objects_len = 0;
}

/**
 * @brief 
 * @param s 
 */
void	scene_clear(t_scene *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (i < s->objects_len)
	{
		if (s->objects_array[i].type == SPHERE
			&& (s->objects_array[i].shape.sp.tex.ptr))
			free(s->objects_array[i].shape.sp.tex.ptr);
		i++;
	}
	if (s->objects_array)
		free(s->objects_array);
	scene_init(s);
}

/**
 * @brief 
 * @param s 
 * @param needed 
 * @return 
 */
int	scene_objs_reserve(t_scene *s, int needed)
{
	t_object	*new_arr;
	int			new_cap;

	if (s->objects_cap >= needed)
		return (0);
	new_cap = s->objects_cap;
	if (new_cap < DFLT_OBJ_CAP)
		new_cap = DFLT_OBJ_CAP;
	while (new_cap < needed)
		new_cap = new_cap * 2;
	new_arr = (t_object *)ft_calloc(new_cap, sizeof(*new_arr));
	if (!new_arr)
		return (1);
	if (s->objects_len > 0)
		ft_memcpy(new_arr, s->objects_array, sizeof(*new_arr) * s->objects_len);
	free(s->objects_array);
	s->objects_array = new_arr;
	s->objects_cap = new_cap;
	return (0);
}
