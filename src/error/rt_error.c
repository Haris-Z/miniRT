/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:09:01 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:20:34 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>

//#include "mrt.h"

#include "libft.h"
#include "rt_error.h"


static const char	*rt_strerror(t_eflag e);
static void			rt_parse_err(int i, char *msg, char *arg);

int	rt_error_msg(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/**
 * @brief 
 * 
 * @param code 
 * @param msg 
 * @param i 
 * @return int
 * @todo split function - check for msg NULL arg NULL
 */
int	rt_error_log(int code, const char *msg, int i, char *arg)
{
	if (code > E_PARSE_BASE && code < E_PARSE_END)
	{
		rt_parse_err(i, (char *)rt_strerror(code), arg);
		if (msg)
			ft_putendl_fd((char *)msg,2);
		ft_putstr_fd("\n", 2);
		return (code);
	}
	if (code > E_RT_BASE && code < E_RT_END)
	{
		ft_putendl_fd((char *)MSG_ERROR, 2);
		ft_putstr_fd("[RT]: ", 2);
		ft_putendl_fd((char *)rt_strerror(code), 2);
		return(code);
	}
	if (code == E_SYS)
	{
		ft_putendl_fd((char *)MSG_ERROR, 2);
		ft_putstr_fd("[SYS]: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (code);
	}
	rt_error_msg((char *)msg);
	return (code);
}

static void	rt_parse_err(int i, char *msg, char *arg)
{
	ft_putstr_fd(MSG_ERROR, 2);
	ft_putstr_fd("[PARSE]: ", 2);
	if (i)
	{
		ft_putstr_fd("Line ", 2);
		ft_putnbr_fd(i, 2);
		ft_putstr_fd(": ", 2);
		if (arg)
		{
			ft_putstr_fd("(", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(") ", 2);
		}
	}
	if (msg)
		ft_putstr_fd(msg, 2);
}

/**
 * @brief 
 * 
 * @param e 
 * @return const char* 
 */
static const char	*rt_strerror(t_eflag e)
{
	const char	*msgs[E_COUNT] = {
	[E_OK] = "Success",
	[E_FILE_EXT] = MSG_FILE_EXT, [E_FILE_EMPTY] = MSG_FILE_EMPTY,
	[E_PARSE_UNKNOWN_ID] = MSG_PARSE_ID,
	[E_PARSE_FORMAT_C] = MSG_FORMAT_C,
	[E_PARSE_FORMAT_A] = MSG_FORMAT_A,
	[E_PARSE_FORMAT_L] = MSG_FORMAT_L,
	[E_PARSE_FORMAT_SP] = MSG_FORMAT_SP,
	[E_PARSE_FORMAT_PL] = MSG_FORMAT_PL,
	[E_PARSE_FORMAT_CY] = MSG_FORMAT_CY,
	[E_BAD_PARAM] = MSG_SP_D,
	[E_PARSE_INVALID_LINE] = MSG_INVALID_LINE,
	[E_PARSE_BAD_FLOAT] = MSG_PARSE_BAD_FLOAT,
	[E_PARSE_BAD_INT] = MSG_PARSE_BAD_INT,
	[E_PARSE_BAD_COLOR] = MSG_PARSE_BAD_COLOR,			// "Invalid RGB color for "
	[E_PARSE_BAD_VEC] = MSG_PARSE_BAD_VEC,		// "Unit vector is zero for "
	[E_PARSE_BAD_VEC3_NORM] = MSG_PARSE_BAD_NORMAL,		// "Vector must be normalized for "
	[E_PARSE_BAD_RATIO] = MSG_PARSE_BAD_RATIO,			// "Invalid ratio for "
	[E_PARSE_BAD_FOV] = MSG_PARSE_BAD_FOV,			// "Camera (C): invalid FOV"
	[E_PARSE_RANGE_FOV] = MSG_PARSE_BAD_FOV,			// "Camera (C): FOV out of range [0..180]"
	[E_PARSE_RANGE_RATIO] = MSG_PARSE_BAD_RATIO,		// "Ratio out of range [0..1] for "
	[E_PARSE_RANGE_COLOR] = MSG_PARSE_BAD_COLOR,		// "RGB out of range for "
	[E_PARSE_RANGE_VEC3] = MSG_PARSE_BAD_UNIT_VEC,	
	[E_PARSE_DUPLICATE_A] = MSG_DUPLICATE_A,
	[E_PARSE_DUPLICATE_C] = MSG_DUPLICATE_C,
	[E_PARSE_DUPLICATE_L] = MSG_DUPLICATE_L,
	[E_PARSE_MISSING_TOKEN] = MSG_MISSING_TOKEN,
	[E_RT_MLX_INIT] = MSG_RT_MLX_INIT,				// "Failed to Initialize mlx."
	[E_RT_WIN_CREATE] = MSG_RT_WIN_CREATE,			// "Errror\n Failed to initialize mlx_window ... "
	[E_RT_IMG_CREATE] = MSG_RT_IMG_CREATE,			// "Failed to initialize mlx_image ... "
	};

	if ((int)e < 0 || e >= E_COUNT)
		return ("Unknown Error");
	if (msgs[e] == 0)
		return ("Unknown error message");
	return (msgs[e]);
}
