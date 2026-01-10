/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:09:01 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/10 12:53:33 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_error.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

static const char	*rt_strerror(t_eflag e);
static void			rt_parse_err(int i, char *msg, char *arg);

int	rt_error_msg(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
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
 * @todo split function - check for msg NULL arg NULL, param arg not in use currently
 */
int	rt_log_error(int code, const char *msg, int i, char *arg)
{
	(void)arg;
	(void)msg;
	if (code > E_PARSE_BASE && code < E_PARSE_END)
	{
		rt_parse_err(i, (char *)rt_strerror(code), arg);
		return (code);
	}
	else if (code > E_RT_BASE && code < E_RT_END)
	{
		ft_putendl_fd(E_MSG, 2);
		ft_putstr_fd("[RT]", 2);
		ft_putendl_fd((char *)rt_strerror(code), 2);
	}
	else if (code == E_SYS)
	{
		ft_putendl_fd(E_MSG, 2);
		ft_putstr_fd("[SYS]: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		// ft_putstr_fd(strerror(errno), 2);
		// ft_putstr_fd(" | ", 2);
		// ft_putnbr_fd(errno, 2);
		// ft_putendl_fd("", 2);
	}
	else
	{
		ft_putendl_fd(E_MSG, 2);
		ft_putendl_fd((char *)msg, 2);
	}
	return (code);
}
// int	rt_log_error(int code, const char *msg, int i, char *arg)
// {
// 	(void)arg;
// 	ft_putendl_fd(E_MSG, 2);
// 	if (code > E_PARSE_BASE && code < E_PARSE_END)
// 	{
// 		ft_putstr_fd("[PARSE] ", 2);
// 		if (i >= 0)
// 		{
// 			ft_putstr_fd("Line ", 2);
// 			ft_putnbr_fd(i, 2);
// 			ft_putstr_fd(": ", 2);
// 		}
// 		ft_putendl_fd((char *)rt_strerror(code), 2);
// 		if (arg)
// 			ft_putstr_fd(arg, 2);
// 		return (code);
// 	}
// 	else if (code > E_RT_BASE && code < E_RT_END)
// 	{
// 		ft_putstr_fd("[RT]", 2);
// 		ft_putendl_fd((char *)rt_strerror(code), 2);
// 	}
// 	else if (code == E_SYS)
// 	{
// 		ft_putstr_fd("[SYS]: ", 2);
// 		ft_putendl_fd(strerror(errno), 2);
// 		// ft_putstr_fd(strerror(errno), 2);
// 		// ft_putstr_fd(" | ", 2);
// 		// ft_putnbr_fd(errno, 2);
// 		// ft_putendl_fd("", 2);
// 	}
// 	else
// 		ft_putendl_fd((char *)msg, 2);
// 	return (1);
// }

static void rt_parse_err(int i, char *msg, char *arg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("[PARSE]: ", 2);
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
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
	[E_USAGE] = ERR_USAGE,
	[E_PARSE_EMPTY_FILE] = MSG_PARSE_EMPTY_FILE,
	[E_RT_MLX_INIT] = MSG_RT_MLX_INIT,
	[E_PARSE_UNKNOWN_ID] = MSG_PARSE_UNKNONW_ID,
	[E_PARSE_TRAILING_GARBAGE] = MSG_TRAILING_GARBAGE,
	[E_PARSE_DUPLICATE_AMBIENT] = MSG_PARSE_DUPLICATE_AMBIENT
	};

	if ((int)e < 0 || e >= E_COUNT)
		return ("Unknown Error");
	if (msgs[e] == 0)
		return ("Unknown error message");
	return (msgs[e]);
}
