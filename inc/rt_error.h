/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:45:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/07 18:43:05 by hazunic          ###   ########.fr       */
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
 * 	- [x] add tests
 * 	- [x] add error message list
 * 	- [x] add functions for internal messages and for system errors messages
 *  - [ ] no defines just use messages directly
 */

#ifndef RT_ERROR_H
# define RT_ERROR_H

// Mandatory for Subject
# define E_MSG "Error"
# define ERR_USAGE "./miniRT /path/to/file.rt"

// Parsing Errors
# define ERR_PARSE_A_MSG " add message here ... "
# define ERR_UNEXPECTED_TOKEN "%s: unexpected token \"%s\""
# define ERR_RTFILE_L " add message "

// MLX errors
# define ERR_MLX_INIT_MSG " Failed to "

/**
 * @brief struct containing error codes for miniRT
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
	E_PARSE_BAD_COLOR,
	E_PARSE_BAD_VEC3,
	E_PARSE_RANGE_FOV,
	E_PARSE_DUPLICATE_AMBIENT,
	E_PARSE_DUPLICATE_CAMERA,
	E_PARSE_DUPLICATE_LIGHT,
	E_PARSE_MISSING_TOKEN,
	E_PARSE_TRAILING_GARBAGE,
	E_PARSE_END,
	E_RT_BASE,
	E_RT_MLX_INIT,
	E_RT_WIN_CREATE,
	E_RT_IMG_CREATE,
	E_RT_BAD_SCENE_STATE,
	E_RT_NO_CAMERA,
	E_RT_END,
	E_SYS,
	E_COUNT
}	t_eflag;

int		rt_log_error(int code, const char *msg, int i);

#endif // RT_ERROR_H