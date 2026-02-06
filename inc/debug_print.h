/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:22:35 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/06 16:27:42 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_PRINT_H
# define DEBUG_PRINT_H


# include "mrt.h"

void	print_scene_info(t_scene scene, char *file);
void	printV(t_vec3 a);
void	printM(t_mat3 a);

#endif // DEBUG_PRINT_H