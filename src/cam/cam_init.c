/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:25:13 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/12 08:31:22 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cam.h"

int	cam_init(t_camera *cam, int width, int height, t_cam_rt *out)
{
	double	aspect;

	if (!cam || !out || width <= 0 || height <= 0)
		return (1);
	aspect = (double)width / (double)height;
	out->origin = cam->pos;
	out->forward = vec_norm(cam->dir);
	out->w = width;
	out->h = height;
	cam_build_basis(out->forward, &out->right, &out->up);
	calc_viewport(cam->fov_deg, aspect, &out->w_viewport, &out->h_viewport);
	return (0);
}
