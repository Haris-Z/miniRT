/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:50:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/12 22:58:54 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"

static void	obj_free_list(t_obj *o)
{
	t_obj	*next;

	while (o)
	{
		next = o->next;
		free(o);
		o = next;
	}
}

void	scene_clear(t_scene *s)
{
	if (!s)
		return ;
	
	obj_free_list(s->objs);
	s->objs = NULL;
	
	if (s->objs_arr)
	{
		free(s->objs_arr);
		s->objs_arr = NULL;
		s->objs_n = 0;
	}
	// reset rest?
}
