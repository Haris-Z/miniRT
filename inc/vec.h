/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:33:29 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:14:37 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef VEC_H
// # define VEC_H

// # define RADIAN 57.2958

// //  p = (x,y,z)
// // 3d vec
// typedef struct s_vec3
// {
// 	double	x;
// 	double	y;
// 	double	z;
// }	t_vec3;

// /**
//  * @brief create a vector 
//  * 
//  * @param x 
//  * @param y 
//  * @param z 
//  * @return t_vec3 
//  */
// t_vec3	vec3(double x, double y, double z);

// // basic vector operations

// /**
//  * @brief 
//  * 
//  * @param a 
//  * @param b 
//  * @return t_vec3 
//  */
// t_vec3	vec_add(t_vec3 a, t_vec3 b);

// /**
//  * @brief 
//  * 
//  * @param a 
//  * @param b 
//  * @return t_vec3 
//  */
// t_vec3	vec_sub(t_vec3 a, t_vec3 b);

// /**
//  * @brief 
//  * 
//  * @param v 
//  * @return t_vec3 
//  */
// t_vec3	vec_neg(t_vec3 v);

// /**
//  * @brief 
//  * 
//  * @param v 
//  * @param s 
//  * @return t_vec3 
//  */
// t_vec3	vec_scale(t_vec3 v, double s);

// /**
//  * @brief 
//  * 
//  * @param a 
//  * @param b 
//  * @return t_vec3 
//  */
// t_vec3	vec_mul(t_vec3 a, t_vec3 b);

// /**
//  * @brief 
//  * 
//  * @param a 
//  * @param b 
//  * @return double 
//  */
// double	vec_dot(t_vec3 a, t_vec3 b);

// /**
//  * @brief 
//  * 
//  * @param a 
//  * @param b 
//  * @return t_vec3 
//  */
// t_vec3	vec_cross(t_vec3 a, t_vec3 b);


// /**
//  * @brief 
//  * 
//  * @param v 
//  * @return double 
//  */
// double	vec_len(t_vec3 v);

// /**
//  * @brief 
//  * 
//  * @param v 
//  * @return t_vec3 
//  */
// t_vec3	vec_norm(t_vec3 v);

// // utils

// /**
//  * @brief 
//  * 
//  * @param v 
//  * @return int 
//  */
// int		vec_near_zero(t_vec3 v);

// /**
//  * @brief 
//  * 
//  * @param v 
//  * @param n 
//  * @return t_vec3 
//  */
// t_vec3	vec_reflect(t_vec3 v, t_vec3 n);
// void	printV(t_vec3 a);
// double	getDistBetweenPoints(t_vec3 pointA, t_vec3 pointB);

// #endif // VEC_H
