/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:45:42 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 17:31:31 by hazunic          ###   ########.fr       */
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
 * 	- [ ] add error message list
 * 	- [ ] add functions for internal messages and for system errors messages
 */

#ifndef RT_ERROR_H
# define RT_ERROR_H

/*
** Error messages
*/

// Mandatory for Subject
# define ERR_MSG "Error\n"

// Parsing Errors
# define USAGE "./miniRT /path/to/file.rt\n"
# define ERR_PARSE_A_MSG " add message here %s %d ... "
# define ERR_UNEXPECTED_TOKEN "%s: unexpected token \"%s\""
# define ERR_RTFILE_L " add message "

// MLX errors
# define ERR_MLX_INIT_MSG " Failed to "


/**
 * @brief struct containing error codes for miniRT
 * 
 * 	E_USAGE = 0,		USAGE "./miniRT /path/to/file.rt\n"
 *	E_PARSE_A_FLAG,
 *	E_PARSE_C_FLAG,
 *	E_PARSE_L_FLAG,
 *	E_PARSE_SP_FLAG,
 *	E_SYS,
 *	ERR_COUNT
 * 
 */
typedef enum e_eflag
{
	E_USAGE = 0,
	E_PARSE_A_FLAG,
	E_PARSE_C_FLAG,
	E_PARSE_L_FLAG,
	E_PARSE_SP_FLAG,
	E_SYS,
	ERR_COUNT
	// ...
}	t_eflag;

/* note: not in use yet/not needed */
typedef struct s_err_ctx
{
	int			code;
	char		*errarg;
	int			pos;
	const char	*errinfo;
}	t_err_ctx;


int			rt_error(int code, const char *msg);
const char	*rt_strerror(int code);

/* note:  not in use yet/not needed */
void		error_ctx_init(t_err_ctx *ctx);
void		error_ctx_set(t_err_ctx *ctx, int code, int pos, char *arg);

#endif // RT_ERROR_H