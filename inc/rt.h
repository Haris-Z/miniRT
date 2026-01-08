/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:13:51 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 16:33:24 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file	rt.h
 * @brief	This file contains ... (add more info later)
 * 
 */

#ifndef RT_H
# define RT_H

# define RT_WINDOW_NAME	"miniRT"
# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600

# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>			// contatins keycodes
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "rt_error.h"

// # include "vec3.h"
// # include "ray.h"
// # include "color.h"
// # include "scene.h"
// # include "parser.h"

/**
 * @brief 
 * 
 */
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;		// set ?
	int		line_len;	// set ?
	int		endian;		// set ?
	int		img_w;
	int		img_h;
}	t_img;

/**
 * @brief 
 * 
 */
typedef struct s_rt_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		w;
	int		h;
	// int screendim[2]
	int		should_quit;
	//t_scene	scene;
	// err_context
	// state
	// flag
}	t_rt_mlx;

/* app */

/**
 * @brief 
 * 
 * @param rt 
 * @param w 
 * @param h 
 * @param title 
 * @return int 
 */
int		rt_init(t_rt_mlx *rt, int w, int h, const char *title);

/**
 * @brief 
 * 
 * @param rt 
 * @return int 
 */
int		rt_run(t_rt_mlx *rt);

/**
 * @brief 
 * 
 * @param rt 
 */
void	rt_destroy(t_rt_mlx *rt);

/* mlx image wrapper */

/**
 * @brief 
 * 
 * @param rt 
 * @param img 
 * @param w 
 * @param h 
 * @return int 
 */
int		rt_img_create(t_rt_mlx *rt, t_img *img, int w, int h);

/**
 * @brief 
 * 
 * @param rt 
 * @param img 
 */
void	rt_img_destroy(t_rt_mlx *rt, t_img *img);

/**
 * @brief 
 * 
 * @param img 
 * @param x 
 * @param y 
 * @param color 
 */
void	rt_img_put_pixel(t_img *img, int x, int y, int color);

/* events/hooks */

/**
 * @brief 
 * 
 * @param keycode 
 * @param param 
 * @return int 
 */
int		rt_on_keypress(int keycode, void *param);

/**
 * @brief 
 * 
 * @param param 
 * @return int 
 */
int		rt_on_destroy(void *param);

/**
 * @brief 
 * 
 * @param param 
 * @return int 
 */
int		rt_on_expose(void *param);

/**
 * @brief 
 * 
 * @param param 
 * @return int 
 */
int		rt_on_loop(void *param);

#endif
