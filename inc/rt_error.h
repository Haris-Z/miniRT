/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:45:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 17:03:14 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file	rt_error.h
 * @brief	This file contains error info etc ... (add more info later)
 * 
 */

/**
 * 	- [x] check my minishell for error context + sys errors
 * 	- [x] add enum for error codes
 * 	- [ ] add defines for error messages
 * 	- [ ] add Tracelogger from other project
 * 	- [x] add includes - errno.h string.h in files
 * 	- [ ] add tests
 * 	- [x] add error message list
 * 	- [x] add functions for internal messages and for system errors messages
 */

#ifndef RT_ERROR_H
# define RT_ERROR_H

// all messages in one place - easier to change later

// Mandatory for Subject
# define E_MSG "Error"
# define ERR_USAGE "./miniRT /path/to/file.rt" // -> 

// Parsing Errors
# define ERR_PARSE_A_MSG " add message here ... "
# define ERR_UNEXPECTED_TOKEN "%s: unexpected token \"%s\""
# define ERR_RTFILE_L " add message "

// MLX errors
# define MSG_RT_MLX_INIT "Failed to Initialize mlx."
# define MSG_RT_MLX_INIT "Failed to Initialize mlx."
# define MSG_RT_WIN_CREATE "Errror\n Failed to initialize mlx_window ... "
# define MSG_RT_IMG_CREATE "Failed to initialize mlx_image ... "


/**
 * @brief	struct containing error codes for miniRT
 * 			corresponding error message defined with prefix MSG 
 */
typedef enum e_eflag
{
	E_OK = 0,					// Success
	E_USAGE,					// "./miniRT /path/to/file.rt"
	E_PARSE_BASE,
	E_PARSE_EMPTY_FILE,
	E_PARSE_UNKNOWN_ID,
	E_PARSE_BAD_FLOAT,
	E_PARSE_BAD_INT,
	E_PARSE_BAD_COLOR,			// "Invalid RGB color for "
	E_PARSE_BAD_VEC3_ZERO,		// "Unit vector is zero for "
	E_PARSE_BAD_VEC3_NORM,		// "Vector must be normalized for "
	E_PARSE_BAD_RATIO,			// "Invalid ratio for "
	E_PARSE_BAD_FOV,			// "Camera (C): invalid FOV"
	E_PARSE_RANGE_FOV,			// "Camera (C): FOV out of range [0..180]"
	E_PARSE_RANGE_RATIO,		// "Ratio out of range [0..1] for "
	E_PARSE_RANGE_COLOR,		// "RGB out of range for "
	E_PARSE_RANGE_VEC3,			// "Unit vector components out of range [-1..1] for "
	E_PARSE_DUPLICATE_AMBIENT,
	E_PARSE_DUPLICATE_CAMERA,
	E_PARSE_DUPLICATE_LIGHT,
	E_PARSE_MISSING_AMBIENT,
	E_PARSE_MISSING_CAMERA,
	E_PARSE_MISSING_LIGHT,
	E_PARSE_MISSING_TOKEN,
	E_PARSE_TRAILING_GARBAGE,
	E_PARSE_END,
	E_RT_BASE,					// "[PARSE] | "
	E_RT_MLX_INIT,				// "Failed to Initialize mlx."
	E_RT_WIN_CREATE,			// "Errror\n Failed to initialize mlx_window ... "
	E_RT_IMG_CREATE,			// "Failed to initialize mlx_image ... "
	E_RT_GET_ADDRESS,			// "Failed to initalize .. "  -- ?
	E_RT_BAD_SCENE_STATE,
	E_RT_NO_CAMERA,
	E_RT_END,
	E_SYS,
	E_NONE,
	E_COUNT
}	t_eflag;


/**
 * @brief 
 * 
 * @param code 
 * @param msg 
 * @param i 
 * @param arg 
 * @return int 
 */
int	rt_log_error(int code, const char *msg, int i, char *arg);

#endif // RT_ERROR_H