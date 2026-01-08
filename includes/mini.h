#ifndef MINI_RT_H
# define MINI_RT_H

# define EPSILON 0.0000001
# define RADIAN 57.2958

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

typedef struct s_ray
{
	vector	direction;
	double	dist;
	t_item	*closestitem;
} t_ray;

//stuff for the simulation
typedef struct s_camera
{
	vector	orientation;
	vector	pos;
	t_item	**items;
	vector	light;
	t_ray	**rays;
	int		pixels[2];
	double		fov;
	double		ambient;
} t_camera;


//struct to feed minilibX
typedef struct	s_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//root struct
typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_camera	*cam;
	t_data		*colors;
}	t_vars;

t_camera	*cam_init(vector pos, vector orientation, int fov, int screendi[2]);
void	kill_cam(t_camera	*cam);
double	hitSp(vector origin ,vector ray, t_sphere sphere);
double	hitPl(vector origin ,vector ray, t_plane plane);
void	updateRayDist(int i, t_vars *vars, t_item *obj);
int	dirVector_init(t_camera *cam);

int	computeColor(t_vars vars, t_ray ray, t_item **items);
double	getLightAngle(vector oPoint, vector dir, t_ray ray, vector light, t_item *items);
int	scaleColor(int min, int max, double amount);

#endif
