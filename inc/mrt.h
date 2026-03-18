/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:13:22 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 18:42:31 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_H
# define MRT_H

# define SCREEN_WIDTH	1980 // make usage of get_window_size_function
# define SCREEN_HEIGHT	1400
# define RT_WINDOW_NAME	"miniRT"

# define RADIAN 57.295779513 // 180/π⁠° ≈ 57.295779513°
# define EPSILON 1e-12
# define BOT_CAP 0
# define TOP_CAP 1
# define NO_HIT -1.0

//# define BONUS 0

# ifndef MAX_LIGHTS
#  define MAX_LIGHTS 1
# endif

// # ifndef MAX_LIGHTS
// #  define MAX_LIGHTS 5
// # else
// #  define MAX_LIGHTS 1
// # endif //BONUS

# define MSAA 1
# define FOCAL_SCALE_EXP 5 // 1 to inf
# define SHINE 12 // 1 to inf

# define DFLT_OBJ_CAP 8

# include <limits.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# include <X11/X.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>

# include <mlx.h>

// # ifndef BONUS
// #  define BONUS 0
// # endif
// ----------- VECTOR -----------
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// ----------- MATRIX -----------
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
}	t_ambient;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	double	diameter;
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
	double	radius;
	double	height;
	t_color	color;
}	t_cylinder;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef	union u_shape
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}	t_shape;

typedef struct s_object
{
	t_type	type;
	t_shape	shape;
	t_color	color;
}	t_object;
	//int	idx?;

// ----------- CAMERA -----------

typedef struct s_ray
{
	t_vec3		direction;
	double		dist;
	t_object	*closestitem;
}	t_ray;

typedef struct s_viewport
{
	double	focalLength;
	double	focusDist;
	double	horRange;
	double	deltaHorAngle;
	double	verRange;
	double	deltaVerRange;
	double	verOffset;
	double	horOffset;
	t_mat3	rotationM;
}	t_viewport;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		dir;
	double		fov_deg;
	t_ray		*rays;
	t_viewport	vp;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	bright;
	t_color	color;
	int		rgb;
}	t_light;

// typedef struct s_scene_elements
// {
// 	t_ambient	amb;
// 	t_camera	cam;
// 	t_light		light[MAX_LIGHTS];
// }	t_elements;
//# ifndef BONUS

typedef struct s_scene
{
	int			has_light;
	int			has_ambient;
	int			has_camera;
	t_ambient	amb;
	t_camera	cam;
	t_light		light[MAX_LIGHTS];
	size_t		light_count;
	t_object	*objects_array;	// make object stack?
	int			objects_len;	// used mem
	int			objects_cap;	// allocated
}	t_scene;

//# endif

// typedef struct s_rt_cam
// {
// 	t_vec3		orientation;
// 	t_vec3		pos;
// 	double		fov;
// }	t_cam_rt;

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
	t_camera	cam; // t_vars colors
	int			w;
	int			h;
}	t_rt_mlx;

// ----------- VECTOR -----------

/// basic vector operations
t_vec3		vec3(double x, double y, double z);
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_neg(t_vec3 v);
t_vec3		vec_scale(t_vec3 v, double s);
t_vec3		vec_mul(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
t_vec3		vec_norm(t_vec3 v);
double		vec_len(t_vec3 v);
double		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		vec_mul_m(t_vec3 v, t_mat3 m);

/// vector utils
int			vec_near_zero(t_vec3 v);
t_vec3		vec_reflect(t_vec3 v, t_vec3 n);
double		get_dist_between_p(t_vec3 pointA, t_vec3 pointB);
t_vec3		reject_axis(t_vec3 v, t_vec3 axis);

/// matrix ops
t_mat3		mat_new(t_vec3 colx, t_vec3 coly, t_vec3 colz);
t_mat3		mat_mult(t_mat3 a, t_mat3 b);
t_mat3		mat_scale(double amount, t_mat3 mat);
t_mat3		mat_add(t_mat3 a, t_mat3 b);
t_mat3		calc_rotation_matrix(t_vec3 axis, double verAngle);

// ----------- COLOR -----------

double		rt_clamp(double x, double min, double max);
t_color		color_rgb(int r, int g, int b);
int			color_to_mlx(t_color c);
t_color		color_normalize(t_color c);
int			color_to_int(t_color c);

// ----------- SCENE -----------

// init and clear
void		scene_init(t_scene *s);
void		scene_clear(t_scene *s);

int			scene_objs_reserve(t_scene *s, int needed);
int			scene_objs_push(t_scene *s, t_object obj);

// init settings from parsing
int			scene_set_ambient(t_scene *s, t_ambient a);
int			scene_set_camera(t_scene *s, t_camera c);
int			scene_set_light(t_scene *s, t_light l);

// init objects from parsing
int			scene_add_sphere(t_scene *s, t_sphere sp);
int			scene_add_plane(t_scene *s, t_plane pl);
int			scene_add_cylinder(t_scene *s, t_cylinder cy);
int			set_default_scene(t_scene *s);

// ----------- MLX / IMAGE -----------

int			rt_init(t_rt_mlx *rt, const char *title);
int			rt_run(t_rt_mlx *rt);
void		rt_destroy(t_rt_mlx *rt);

// mlx wrapper
int			rt_img_create(t_rt_mlx *rt, t_rt_img *img, int w, int h);
void		rt_img_destroy(t_rt_mlx *rt, t_rt_img *img);
void		rt_img_put_pixel(t_rt_img *img, int x, int y, int color);

// events/hooks
int			rt_on_keypress(int keycode, void *param);
int			rt_on_destroy(void *param);
int			rt_on_expose(void *param);
int			rt_on_loop(void *param);

// save to ppm
int			save_to_ppm(const char *path, const t_rt_img *img);

// ----------- CAMERA -----------
t_camera	cam_init(t_scene s);
void		add_dir_vector_row(t_camera *cam, int w);

// ----------- SHADER -----------
t_vec3		get_surface_normal(t_vec3 point, t_vec3 ray_dir, t_object *item);
t_vec3		get_reflection_v(t_vec3 surfaceToLight, t_vec3 surfaceNormal);
// t_color		compute_color(t_rt_mlx vars, t_ray ray,
// 			t_object *objs, int n);
t_color	compute_color(t_scene s, t_ray ray);


// ----------- MINI -----------

// intersections
double		hit_sp(t_vec3 origin, t_vec3 ray, t_sphere *sphere);
double		hit_pl(t_vec3 origin, t_vec3 ray, t_plane plane);

// cylinder intersections
double		hit_cy(t_vec3 origin, t_vec3 ray, t_cylinder *cy);
t_vec3		cy_cap_center(t_cylinder *cy, int top);
t_vec3		cy_normal(t_vec3 p, t_cylinder *cy);

// intersection utils
t_vec3		set_face_normal(t_vec3 ray_dir, t_vec3 outward);
double		min_pos(double a, double b);

// render utils
int			render(t_scene *scene_info, t_rt_mlx *app);
t_ray		get_dir_vector(t_camera *cam, double preCalc[4]);
int			dir_vector_init(t_camera *cam, int w, int h);
double		get_light_angle(t_vec3 oPoint, t_ray ray, t_vec3 light,
			t_object *objs, int n);
t_color		scale_color(t_color min, t_color max, double amount);
void		kill_cam(t_camera	*cam);

#endif // MRT_H
