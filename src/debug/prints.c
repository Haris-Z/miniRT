/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:25:53 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:22:15 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "stdio.h"
#include "libft.h"

void	print_vector(char *name, t_vec3 v)
{
	if (name)
		printf("%s: ", name);
	printf("(%.5f, %.5f, %.5f)", v.x, v.y, v.z);
	printf("\n");
}

void	printV(t_vec3 a)
{
	printf("x: %f y: %f z: %f\n", a.x,a.y,a.z);
}

void	printM(t_mat3 a)
{
	printf("	%f	%f	%f\n", a.colx.x, a.coly.x, a.colz.x);
	printf("	%f	%f	%f\n", a.colx.y, a.coly.y, a.colz.y);
	printf("	%f	%f	%f\n", a.colx.z, a.coly.z, a.colz.z);
}
