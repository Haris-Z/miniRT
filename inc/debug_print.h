/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:22:35 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/06 18:02:46 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_PRINT_H
# define DEBUG_PRINT_H

# include "mrt.h"

// debug prints

void	print_scene_info(t_scene scene, char *file);
void	print_vector(char *name, t_vec3 v);
void	printV(t_vec3 a);
void	printM(t_mat3 a);

#endif // DEBUG_PRINT_H