#ifndef MINI_RT_H
# define MINI_RT_H

# define EPSILON 0.0000001
# define RADIAN 57.2958

# include "vector.h"
# include "scene.h"
# include "cam.h"
# include "rt.h"

typedef struct s_ray t_ray;

// norminette these functions

void		kill_cam(t_cam_rt	*cam);
double		hitSp(t_vec3 origin ,t_vec3 ray, t_sphere sphere);
double		hitPl(t_vec3 origin ,t_vec3 ray, t_plane plane);
void		updateRayDist(int i, t_rt_mlx *vars, t_obj *obj);
int			dirVector_init(t_cam_rt *cam);

int			computeColor(t_rt_mlx vars, t_ray ray, t_obj **items);
double		getLightAngle(t_vec3 oPoint, t_ray ray, t_vec3 light, t_obj *items);
int			scaleColor(int min, int max, double amount);

#endif
