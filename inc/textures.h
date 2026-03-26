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