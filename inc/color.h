/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:40:57 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 20:21:51 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

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

#endif