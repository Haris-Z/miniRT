/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:13:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 12:51:32 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_H
# define MRT_H

# define RADIAN 57.295779513 // 180/π⁠° ≈ 57.295779513°
# define RT_WINDOW_NAME	"miniRT"
# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600
# define EPSILON 1e-12

# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# include <X11/X.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>

# include <mlx.h>
# include "cam.h"

// ----------- VECTOR -----------

//  p = (x,y,z)
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_mat3
{
	t_vec3	colx;
	t_vec3	coly;
	t_vec3	colz;
}	t_mat3;

// ----------- COLOR -----------

typedef t_vec3	t_color;

// ----------- SCENE -----------

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
	int		rgb;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov_deg;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	bright;
	t_color	color;
	int		rgb;
}	t_light;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	double	diameter;
	int		camInside;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;

enum e_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
};
typedef enum e_type			t_type;

struct s_obj
{
	t_type			type;
	union					// i think this is not allowed by norm
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
	t_color			color;
	struct s_obj	*next;
};
typedef struct s_obj		t_obj;

struct s_scene_info
{
	int			has_light;
	int			has_ambient;
	int			has_camera;
	t_ambient	amb;
	t_camera	cam;
	t_light		light;
	t_obj		*objs;
};
typedef struct s_scene_info	t_scene;

// ----------- CAMERA -----------

typedef struct s_ray
{
	t_vec3	direction;
	double	dist;
	t_obj	*closestitem;
}	t_ray;

typedef struct s_rt_cam
{
	t_vec3	orientation;
	t_vec3	pos;
	t_obj	**items;
	t_light	light;
	// t_vec3	light;
	t_ray	*rays;
	t_vec3	*xyTemplate;
	t_mat3	rotationM;
	int		pixels[2];
	double	fov;
	double	ambient;
	double	focalLength;
	double	focusDist;
	double	horRange;
	double	deltaHorAngle;
	double	height;
	double	deltaHeight;
}	t_cam_rt;

// ----------- MLX / IMAGE -----------

typedef struct s_rt_img
{
	void	*ptr;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_w;
	int		img_h;
}	t_rt_img;

typedef struct s_rt_mlx
{
	int			should_quit;
	void		*mlx;
	void		*win;
	t_rt_img	img; // colors
	t_cam_rt	cam; // t_vars colors
	int			w;
	int			h;
}	t_rt_mlx;

// ----------- VECTOR -----------

/// basic vector operations
t_vec3	vec3(double x, double y, double z);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_neg(t_vec3 v);
t_vec3	vec_scale(t_vec3 v, double s);
t_vec3	vec_mul(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_norm(t_vec3 v);
double	vec_len(t_vec3 v);
double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_mul_M(t_vec3 v, t_mat3 m);

/// vector utils
int		vec_near_zero(t_vec3 v);
t_vec3	vec_reflect(t_vec3 v, t_vec3 n);
void	printV(t_vec3 a);
void	printM(t_mat3 a);
double	getDistBetweenPoints(t_vec3 pointA, t_vec3 pointB);

/// matrix ops
t_mat3	matNew(t_vec3 colx, t_vec3 coly, t_vec3 colz);
t_mat3	matMult(t_mat3 a, t_mat3 b);
t_mat3	matScale(double amount, t_mat3 mat);
t_mat3	matAdd(t_mat3 a, t_mat3 b);
t_mat3	calcRotationMatrix(t_vec3 axis, double verAngle);

// ----------- COLOR -----------

double	rt_clamp(double x, double min, double max);
t_color	color_rgb(int r, int g, int b);
int		color_to_mlx(t_color c);
t_color	color_normalize(t_color c);
int		color_to_int(t_color c);

// ----------- SCENE -----------

// init and clear
void	scene_init(t_scene *s);
void	scene_clear(t_scene *s);

// init settings from parsing
int		scene_set_ambient(t_scene *s, t_ambient a);
int		scene_set_camera(t_scene *s, t_camera c);
int		scene_set_light(t_scene *s, t_light l);

// init objects from parsing
int		scene_add_sphere(t_scene *s, t_sphere sp);
int		scene_add_plane(t_scene *s, t_plane pl);
int		scene_add_cylinder(t_scene *s, t_cylinder cy);
int		set_default_scene(t_scene *s);

// ----------- MLX / IMAGE -----------

int		rt_init(t_rt_mlx *rt, const char *title);
int		rt_run(t_rt_mlx *rt);
void	rt_destroy(t_rt_mlx *rt);

// mlx wrapper
int		rt_img_create(t_rt_mlx *rt, t_rt_img *img, int w, int h);
void	rt_img_destroy(t_rt_mlx *rt, t_rt_img *img);
void	rt_img_put_pixel(t_rt_img *img, int x, int y, int color);

// events/hooks
int		rt_on_keypress(int keycode, void *param);
int		rt_on_destroy(void *param);
int		rt_on_expose(void *param);
int		rt_on_loop(void *param);

// test rendering a sphere
void	rt_render_default_sphere(t_rt_mlx *rt);
void	rt_render_default_objs(t_rt_mlx *rt);
// save to ppm
int		save_to_ppm(const char *path, const t_rt_img *img);

// ----------- PARSER -----------

int		parse_file(const char *path, t_scene *s);

// parse utils
int		parse_vec3(const char *tok, t_vec3 *out);
int		parse_int(const char *s, int *out);
int		parse_double(const char *s, double *out);
int		parse_ratio(const char *tok, double *out);
int		parse_color_vec(const char *tok, t_color *out);
int		parse_unit_vec(t_vec3 v);
int		parse_fov(const char *tok, double *out);

// parse scene elements
int		parse_ambient(t_scene *s, char **t);
int		parse_camera(t_scene *s, char **t);
int		parse_light(t_scene *s, char **t);
int		parse_sphere(t_scene *s, char **t);
int		parse_plane(t_scene *s, char **t);
int		parse_cylinder(t_scene *s, char **t);

// ----------- CAMERA -----------

t_cam_rt	cam_init(t_scene s, int w, int h);
void		addDirVectorRow(t_cam_rt *cam);

// ----------- SHADER -----------
t_vec3		getSurfaceNormal(t_vec3 point, t_obj *item);
t_vec3		getReflectionV(t_vec3 surfaceToLight, t_vec3 surfaceNormal);
t_color		computeColor(t_rt_mlx vars, t_ray ray, t_obj **items);
// ----------- MINI -----------

void		kill_cam(t_cam_rt	*cam);
double		hitSp(t_vec3 origin ,t_vec3 ray, t_sphere *sphere);
double		hitPl(t_vec3 origin ,t_vec3 ray, t_plane plane);
void		updateRayDist(t_rt_mlx *vars, t_obj *obj);
int			dirVector_init(t_cam_rt *cam);
double		getLightAngle(t_vec3 oPoint, t_ray ray, t_vec3 light, t_obj *items);
t_color		scaleColor(t_color min, t_color max, double amount);

#endif // MRT_H
