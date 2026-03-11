/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:45:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:11:18 by hazunic          ###   ########.fr       */
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

// mandatory for Subject
# define MSG_ERROR "Error\n"
# define MSG_USAGE "Usage: ./miniRT <../path/to/file.rt>"
// file 
# define MSG_FILE_EXT "Invalid file extension - expect [.rt]"
# define MSG_FILE_EMPTY "File is empty"
# define MSG_FILE_OPEN "Failed to open file"
// general
# define MSG_PARSE_TRAILING "Invalid line: trailing garbage after parameters "
# define MSG_PARSE_ID "Unknown Identifier "
# define MSG_INVALID_LINE "Invalid format: "
# define MSG_FORMAT_C " Camera (C): expected 'C x,y,z nx,ny,nz fov' "
# define MSG_FORMAT_A "Format: expected 'A ratio (r,g,b)' "
# define MSG_FORMAT_L " Light (L): expected 'L x,y,z ratio R,G,B'"
# define MSG_FORMAT_SP "Sphere (sp): expected 'sp x,y,z diameter R,G,B'"
# define MSG_FORMAT_PL "Plane (pl): expected 'pl x,y,z nx,ny,nz R,G,B'"
# define MSG_FORMAT_CY "Cylinder (cy): expected 'cy x,y,z nx,ny,nz diameter height R,G,B'"
//
# define MSG_DIAMETER " diameter must be > 0"
# define MSG_SP_D "Sphere (sp): diameter must be > 0"
// missing scene element
# define MSG_MISSING_TOKEN "Missing parameter(s) "
# define MSG_MISSING_A "ambient (A)"
# define MSG_MISSING_C "camera (C)"
# define MSG_MISSING_L "light (L)"
// duplicates
# define MSG_DUPLICATE_A "Duplicate ambient lighting (A)"
# define MSG_DUPLICATE_C "Duplicate camera (C)"
# define MSG_DUPLICATE_L "Duplicate light (L)"
// validation
# define MSG_PARSE_BAD_FLOAT "Invalid float "
# define MSG_PARSE_BAD_INT "Invalid integer "
//
# define MSG_PARSE_BAD_RATIO "Ratio must be between [0.0,1.0] "
# define MSG_PARSE_BAD_FOV "FOV must be between 0 and 180 degrees"
//
# define MSG_PARSE_BAD_VEC "Invalid vector format (expected: px,py,pz)"
# define MSG_PARSE_BAD_UNIT "Invalid vector format (expected: nx,ny,nz)"
# define MSG_PARSE_BAD_COLOR "RGB values must be between 0 and 255"
//
# define MSG_PARSE_BAD_NORMAL "Normal vector must be normalized (length = 1)"
# define MSG_PARSE_BAD_AXIS "Axis vector must be normalized (length = 1)"
//
# define MSG_PARSE_BAD_POSITIVE "Value must be positive"
# define MSG_PARSE_BAD_UNIT_VEC "Vector components must be between -1 and 1"
// MLX errors
# define MSG_RT_MLX_INIT "Failed to Initialize mlx."
# define MSG_RT_WIN_CREATE "Failed to create window "
# define MSG_RT_IMG_CREATE "Failed to create image "

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
	RT_ERR_HEIGHT
}	t_rt_err;

typedef struct s_rt_file t_rt_file;

//
/**
 * @brief	struct containing error codes for miniRT
 * 			corresponding error message defined with prefix MSG 
 */
typedef enum e_eflag
{
	E_OK = 0,					// Success
	E_SYS,						// Sys errors
	E_PARSE_BASE,
	E_PARSE_UNKNOWN_ID,			// 
	E_PARSE_BAD_FLOAT,
	E_PARSE_BAD_INT,
	E_PARSE_BAD_COLOR,			// "Invalid RGB color for "
	E_PARSE_BAD_VEC,
	E_PARSE_BAD_VEC3_ZERO,		// "Unit vector is zero for "
	E_PARSE_BAD_VEC3_NORM,		// "Vector must be normalized for "
	E_PARSE_BAD_RATIO,			// "Invalid ratio for "
	E_PARSE_BAD_FOV,			// "Camera (C): invalid FOV"
	E_PARSE_RANGE_FOV,			// "Camera (C): FOV out of range [0..180]"
	E_PARSE_RANGE_RATIO,		// "Ratio out of range [0..1] for "
	E_PARSE_RANGE_COLOR,		// "RGB out of range for "
	E_PARSE_RANGE_VEC3,			// "Unit vector components out of range [-1..1] for "
	E_PARSE_DUPLICATE_A,		// "Duplicate ambient lighting (A)"
	E_PARSE_DUPLICATE_C,
	E_PARSE_DUPLICATE_L,
	E_PARSE_FORMAT_C,
	E_PARSE_FORMAT_A,
	E_PARSE_FORMAT_L,
	E_PARSE_FORMAT_SP,
	E_PARSE_FORMAT_PL,
	E_PARSE_FORMAT_CY,
	E_BAD_PARAM,
	E_PARSE_MISSING_AMBIENT,	// remvoe
	E_PARSE_MISSING_CAMERA,		// remove
	E_PARSE_MISSING_LIGHT,		// remove
	E_PARSE_MISSING_TOKEN,		// remove
	E_PARSE_INVALID_LINE,		// "Invalid line contains trailing garbage"
	E_PARSE_END,
	E_RT_BASE,					// "[PARSE] | "
	E_RT_MLX_INIT,				// "Failed to Initialize mlx."
	E_RT_WIN_CREATE,			// "Errror\n Failed to initialize mlx_window ... "
	E_RT_IMG_CREATE,			// "Failed to initialize mlx_image ... "
	E_RT_END,
	E_COUNT
}	t_eflag;


/**
 * @brief
 * 
 * @param msg
 * @return int
 */
int			rt_error_msg(const char *msg);

const char	*rt_file_strerror(t_rt_err err);
void		rt_print_error(const char *path, t_rt_err err, const t_rt_file *f);

const char	*rt_parse_strerror(int err);
void		print_parse_err(int lineno, char *id, int err);//, int sys_errno);

#endif // RT_ERROR_H