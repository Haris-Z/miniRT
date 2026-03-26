/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:45:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/16 19:51:40 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file	rt_error.h
 * @brief	This file contains error info etc ... (add more info later)
 * 
 */

#ifndef RT_ERROR_H
# define RT_ERROR_H

# include <string.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# include "parse.h"
# include "print_colors.h"

typedef enum e_rt_err
{
	RT_SUCCESS = 0,
	RT_ERR_MALLOC,
	RT_ERR_ARG,
	RT_ERR_USAGE,
	RT_ERR_EXT,
	RT_ERR_OPEN,
	RT_ERR_READ,
	RT_ERR_EMPTY,
	RT_ERR_TOK,
	RT_ERR_ID,
	RT_ERR_DUP,
	RT_ERR_LIGHT_COUNT,
	RT_ERR_MISSING,
	RT_ERR_FORMAT,
	RT_ERR_FORMAT_LIGHT,
	RT_ERR_BAD_INT,
	RT_ERR_BAD_FLOAT,
	RT_ERR_BAD_RATIO,
	RT_ERR_RANGE,
	RT_ERR_URANGE,
	RT_ERR_RANGE_COLOR,
	RT_ERR_UZERO,
	RT_ERR_UNORM,
	RT_ERR_RANGE_FOV,
	RT_ERR_DIAMETER,
	RT_ERR_HEIGHT,
	RT_ERR_TEX
}	t_rt_err;

typedef struct s_rt_file	t_rt_file;

//
/**
 * @brief	struct containing error codes for miniRT
 * 			corresponding error message defined with prefix MSG 
 */
typedef enum e_eflag
{
	E_OK = 0,					// Success
	E_RT_MLX_INIT,				// "Failed to Initialize mlx."
	E_RT_WIN_CREATE,			// "Errror\n Failed to init mlx_window ... "
	E_RT_IMG_CREATE,			// "Failed to initialize mlx_image ... "
	E_RT_END,
	E_COUNT
}	t_eflag;

int			rt_error_msg(const char *msg);

const char	*rt_file_strerror(t_rt_err err);
void		rt_print_error(const char *path, t_rt_err err, const t_rt_file *f);

const char	*rt_parse_strerror(int err);
void		print_parse_err(int lineno, char *id, int err);//, int sys_errno);

#endif // RT_ERROR_H