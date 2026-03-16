/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:22:35 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 18:00:43 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Header file for debug prints
 */

#ifndef DEBUG_PRINT_H
# define DEBUG_PRINT_H

# ifndef DEBUG
#  define DEBUG 0
# endif // DEBUG

# include <stdio.h>
# include "mrt.h"

// void	print_scene_info(t_scene scene, char *file);
void	print_vector(char *name, t_vec3 v);
void	printV(t_vec3 a);
void	printM(t_mat3 a);

#endif // DEBUG_PRINT_H