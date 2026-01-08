#ifndef MINI_RT_H
# define MINI_RT_H

# define EPSILON 0.0000001

# include <mlx.h>
# include <stdlib.h>
# include <limits.h>
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# include "../includes/vector.h"

typedef struct s_sphere
{
	double	radius;
	vector	pos;
} t_sphere;

typedef struct s_plane
{
	vector	point;
	vector	orientation;
} t_plane;

typedef struct s_cylinder
{
	double	radius;
	double	height;
	vector	pos;
} t_cylinder;

typedef struct s_item
{
	enum e_type
	{
		PLANE,
		SHPERE,
		CYLINDER
	} t_type;
	union 
	{
		t_plane plane;
		t_sphere sphere;
		t_cylinder cylinder;
	};
	int				color;
	struct s_item	*next;
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
	vector	direction;
	double	dist;
	t_item	*closestitem;
} t_rays;

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
	void		*mlx;
	void		*win;
	t_camera	*cam;
	t_data		*colors;
	double		ambient;
}	t_vars;

t_camera	*cam_init(vector pos, vector orientation, int fov, int screendi[2]);
void	kill_cam(t_camera	*cam);
double	hitSp(vector origin ,vector ray, t_sphere sphere);
double	hitPl(vector origin ,vector ray, t_plane plane);
void	updateRayDist(int screendim, int i, t_vars *vars, t_item *obj, t_rays	*rays);
int	dirVector_init(t_camera *cam);

int	computeColor(t_vars vars, t_rays ray);
double	getLightAngle(vector oPoint, vector dir, t_rays ray, vector light, t_item *items);
int	scaleColor(int min, int max, double amount);

#endif
