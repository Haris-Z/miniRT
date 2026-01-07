#ifndef MINI_RT_H
# define MINI_RT_H

# include <mlx.h>
# include <stdlib.h>
# include <limits.h>
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# include "vector.h"

typedef struct s_item
{
	double	radius;
	vector	pos;
} t_item;

typedef struct s_camera
{
	vector	orientation;
	vector	pos;
	vector	**dirvectors;
	int		pixels[2];
	double		fov;
} t_camera;

typedef struct s_rays
{
	double	dist;
	t_item	*closestitem;
} s_rays;

typedef struct	s_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*colors;
}	t_vars;

t_camera	*cam_init(vector pos, vector orientation, int fov, int screendi[2]);
double	hitSp(vector ray, t_item ball);
int	dirVector_init(t_camera *cam);
#endif