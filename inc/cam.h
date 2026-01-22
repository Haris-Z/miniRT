/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 10:26:38 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/22 15:04:17 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_H
# define CAM_H

# include "scene.h"

typedef struct s_ray
{
	t_vec3	direction;
	double	dist;
	t_obj	*closestitem;
} t_ray;

typedef struct s_rt_cam
{
	t_vec3	orientation;
	t_vec3	pos;
	t_obj	**items;
	t_vec3	light;
	t_ray	*rays;
	int		pixels[2];
	double	fov;
	double	ambient;
	double	focalLength;
	double	focusDist;
	double	horRange;
	double	deltaVerAngle;
	double	deltaHorAngle;
	double	verOffset;
}	t_cam_rt;

// t_cam_rt	*cam_init(t_vec3 pos, t_vec3 orientation, int fov, int screendi[2]);
t_cam_rt	cam_init(t_scene s, int w, int h);
void		addDirVectorRow(t_cam_rt *cam);

//		cam_get_viewport_dimensions():
//		cam_basis();
//		cam_build();
// int		cam_init(t_camera *cam, int width, int height, t_cam_rt *out);
// t_ray	cam_generate_ray(t_cam_rt cam, int px, int py);
// void	cam_build_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up);
// // get vp dimensions
// void	calc_viewport(double fov_deg, double aspect,
// 						double *width, double *height);

#endif //CAM_H
