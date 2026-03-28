/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:01:40 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/28 22:01:45 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "vec.h"

typedef struct s_tex
{
	void	*ptr;
	int		h;
	int		w;
	int		color_depth;
}	t_tex;

int		parse_tex(const char *t, t_tex *out);
int		get_tex_index(t_vec3 surface_normal, t_tex tex);

#endif