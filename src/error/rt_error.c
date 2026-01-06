/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:09:01 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/06 16:16:04 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_error.h"
#include <stdio.h>
#include "../../libs/libft/inc/libft.h"
#include <errno.h>
#include <string.h>

static const char	*error_messages(int code);
static const char	*error_code_str(int code);

//extern void	ft_putstr_fd(char *s, int fd);

int	rt_error(int code, const char *msg)
{
	if (code == E_SYS)
		fprintf(stderr, "Error: %s\n", strerror(errno));
	else
		fprintf(stderr, rt_strerror(code), msg);
	return (1);
}

/**
 * @brief initialize context for error with default values
 */
void	error_ctx_init(t_err_ctx *ctx)
{
	if (!ctx)
		return ;
	ft_bzero(ctx, sizeof(t_err_ctx));
}

/**
 * @brief Set error context values
 * @todo add return FATAL for E_MALLOC/E_VALID and exit the program?
 * 		- or just set an error_list and print at the end?
 * @usage - if (error_count > 0)
 * 				print_error()
 * 			return (false) return (), exit etc.
 * for fata- like E_MALLC - E_INVALID -> return FATAL and leave.
 */
void	error_ctx_set(t_err_ctx *ctx, int code, int pos, char *arg)
{
	const char	*empty = "";
	
	if (!ctx)
		return ;
	if (!arg)
		ctx->errarg = (char *)empty;
	else
		ctx->errarg = arg;
	ctx->code = code;
	ctx->pos = pos;
	ctx->errinfo = error_messages(code);
}

/**
 * @brief Get error message string with bounds checking
 */
const char	*rt_strerror(int code)
{
	const char	*msgs[ERR_COUNT];

	*msgs = error_messages(code);
	if (code >= ERR_COUNT || msgs[code] == NULL)
		return ("Invalid error code");
	return (msgs[code]);
}

static const char *error_messages(int code)
{
	const char *msgs[ERR_COUNT] = {
		[E_USAGE] = USAGE,
	};

	if ((int)code < 0 || code >= ERR_COUNT)
		return ("Invalid error code");
	return (msgs[code]);
}

// static const char *error_code_str(t_error code)
// {
// 	const char *msgs[ERROR_COUNT] = {
// 		[SUCCESS] = "SUCCESS",
// 		[FAILURE] = "FAILURE",
// 		[E_MALLOC] = "E_MALLOC",
// 		[E_SYNTAX] = "E_SYNTAX",
// 		[E_INVALID] = "E_INVALID",
// 		[E_MISSING_QUOTE] = "E_MISSING_QUOTE",
// 		[E_EOF] = "E_EOF",
// 		[E_HERE_CTRLD] = "E_HERE_CTRLD",
// 	};

// 	if ((int)code < 0 || code >= ERROR_COUNT)
// 		return ("Invalid error code");
// 	return (msgs[code]);
// }