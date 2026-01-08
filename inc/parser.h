/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:49:47 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 16:22:25 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// # include "scene.h"

typedef struct s_scene t_scene;

/**
 * @brief 
 * 
 * @param path 
 * @param s 
 * @return int 
 */
int	parse_rt_file(const char *path, t_scene *s);

#endif