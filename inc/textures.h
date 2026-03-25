#ifndef TEXTURES_H
# define TEXTURES_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_tex
{
	void	*ptr;
	int		h;
	int		w;
	int		color_depth;
}	t_tex;

int	parse_tex(const char *t, t_tex *out);

#endif