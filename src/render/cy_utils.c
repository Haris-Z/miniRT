/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:05:10 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 11:11:10 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/*#########################################################################*/
/* ray-cylinder intersection (called in update_ray_dist and dist_visible() */
/*#########################################################################*/

/*
** get all cylinder intersections
**	- side, top/bot-cap and get closest positive hit.
** @return nearest hit distance > 0, else -1.0
*/
t_vec3	cy_cap_center(t_cylinder *cy, int top)
{
	double	half_height;

	half_height = cy->height * 0.5;
	if (top)
		return (vec_add(cy->center, vec_scale(cy->axis, half_height)));
	return (vec_sub(cy->center, vec_scale(cy->axis, half_height)));
}

/*
** utils
** check if point p lies on the cap plane
** cap is a plane perpendicular to cy->axis, goes trough center of cap
** if p is on plane:
**   dot(p - cap, axis) == 0 + epsilon tolerance
** returns true if p is on the cap plane or close --> else 0.
*/
static int	is_on_cap(t_vec3 p, t_vec3 cap, t_cylinder *cy)
{
	double	d; // distance alonx axis from cap plane

	// vec_sub(p, cap) = v from cap to center p
	// project vec on axis direction
	// if p on plane, than d ~ 0
	d = vec_dot(vec_sub(p, cap), cy->axis);
	return (fabs(d) <= 5.0 * EPSILON); // to avoid cap, hits getting treated as side hits
}

/*
** compute outward normal on the curved side at hit point p.
** side normal == radial direction from the axis line to p.
** returns: unit/norm v outward normal for side surface.
*/
static t_vec3	cy_side_normal(t_vec3 p, t_cylinder *cy)
{
	t_vec3	cp; // v from cy->center to point p
	t_vec3	r;  // (x,y,0)

	cp = vec_sub(p, cy->center); // from center to hit point
	r = reject_axis(cp, cy->axis);
	return (vec_norm(r));
}

/*
** compute correct normal for cylinder parts
** top cap    = normal = +axis
** bottom cap = normal = -axis
** side       = normal = radial direction
*/
t_vec3	cy_normal(t_vec3 p, t_cylinder *cy)
{
	t_vec3	top; // top cap center
	t_vec3	bot; // bot cap center
	t_vec3	n; // normal

	bot = cy_cap_center(cy, BOT_CAP);
	top = cy_cap_center(cy, TOP_CAP);
	if (is_on_cap(p, top, cy))
		n = cy->axis;						// outward for top cap
	else if (is_on_cap(p, bot, cy))
		n = vec_scale(cy->axis, -1.0); // outwarod for bot
	else
		n = cy_side_normal(p, cy);			// outward for sid
	return (vec_norm(n));
}