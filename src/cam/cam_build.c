/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:01:26 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:47:36 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cam.h"
#include "hit.h"
#include "ray.h"

static t_vec3	get_up_vec(t_vec3 fwd)
{
	t_vec3	up;
	double	dot;

	up = vec3(0.0, 1.0, 0.0);
	dot = fabs(vec_dot(fwd, up));
	if (dot > 0.999)
		up = vec3(0.0, 0.0, 1.0);
	return (up);
}

static double	deg_2_rad(double d)
{
	return (d * (3.14159265358979323846 / 180.0)); // add math.h M_PI
}

// ortho basis			t_cam_rt *fru
void	cam_build_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up)
{
	t_vec3	up_vec;
	double	len;

	up_vec = get_up_vec(forward);
	*right = vec_cross(up_vec, forward);
	len = vec_len(*right);
	if (len < 0.0001)
	{
		up_vec = (t_vec3){0.0, 0.0, 1.0}; // also alloweed by norm
		*right = vec_cross(up_vec, forward);
	}
	*right = vec_norm(*right);
	*up = vec_cross(forward, *right);
}

// get vp dimensions
void	calc_viewport(double fov_deg, double aspect,
						double *width, double *height)
{
	double	half_fov;

	half_fov = tan(deg_2_rad(fov_deg) * 0.5);
	*width = 2.0 * half_fov;
	*height = *width / aspect;
}
