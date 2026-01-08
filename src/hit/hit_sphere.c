/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:00:55 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 22:00:56 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

double	hitSp(vector ray, t_item ball)
{

	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dotv(ray, ray);
	b = -2.0 * dotv(ray, ball.pos);
	c = dotv(ball.pos, ball.pos) - ball.radius * ball.radius;
	discriminant = (b*b - 4*a*c);
	// printf("discriminant: %f\n", discriminant);
	if (discriminant < 0)
		return -1.0;
	else {
		return (-b - sqrt(discriminant) ) / (2.0*a);
	}
}