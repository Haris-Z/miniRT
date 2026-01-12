/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 10:26:38 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:31:08 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_H
# define CAM_H

# include "scene.h"
# include "ray.h"

typedef struct s_cam_rt
{
	t_vec3	origin;
	t_vec3	forward;		// look direction f
	t_vec3	right;			// f x u normalized
	t_vec3	up;				// up vector u
	double	w_viewport;
	double	h_viewport;
	int		w;
	int		h;
	double	aspect_ratio;
}	t_cam_rt;

//		cam_get_viewport_dimensions():
//		cam_basis();
//		cam_build();
int		cam_init(t_camera *cam, int width, int height, t_cam_rt *out);
t_ray	cam_generate_ray(t_cam_rt cam, int px, int py);
void	cam_build_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up);
// get vp dimensions
void	calc_viewport(double fov_deg, double aspect,
						double *width, double *height);

#endif //CAM_H
