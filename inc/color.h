/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:40:57 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/23 21:02:48 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "cam.h"
# include "vec.h"

typedef t_vec3	t_color;

/**
 * @brief 
 * 
 * @param x 
 * @param min 
 * @param max 
 * @return double 
 */
double	rt_clamp(double x, double min, double max);

/**
 * @brief 
 * 
 * @param r 
 * @param g 
 * @param b 
 * @return t_color 
 */
t_color	color_rgb(int r, int g, int b);

/**
 * @brief 
 * 
 * @param c 
 * @return int 
 */
int		color_to_mlx(t_color c);


t_color	color_normalize(t_color c);
int		color_to_int(t_color c);

#endif