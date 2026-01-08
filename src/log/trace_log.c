/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:31:10 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 09:39:51 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_log.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Default = LOG_ERROR  
 * You can change it at runtime with rt_log_set_level() or rt_log_cycle_level().
 */
static t_log_level	g_log_level = LOG_ERROR;

static const char	*lvl_name(t_log_level lvl)
{
	if (lvl == LOG_TRACE)
		return ("TRACE");
	if (lvl == LOG_DEBUG) return "DEBUG";
	if (lvl == LOG_INFO) return "INFO";
	if (lvl == LOG_WARNING) return "WARNING";
	if (lvl == LOG_ERROR) return "ERROR";
	if (lvl == LOG_FATAL) return "FATAL";
	if (lvl == LOG_ALL) return "ALL";
	if (lvl == LOG_NONE) return "NONE";
	return "LOG";
}

static int	should_print(t_log_level msg_lvl)
{
	if (g_log_level == LOG_NONE)
		return 0;
	if (g_log_level == LOG_ALL)
		return 1;
	return (msg_lvl >= g_log_level);
}

void	rt_log_set_level(t_log_level lvl)
{
	g_log_level = lvl;
}

t_log_level	rt_log_get_level(void)
{
	return (g_log_level);
}

void	rt_log_cycle_level(void)
{
	if (g_log_level == LOG_ERROR)
		g_log_level = LOG_WARNING;
	else if (g_log_level == LOG_WARNING)
		g_log_level = LOG_INFO;
	else if (g_log_level == LOG_INFO)
		g_log_level = LOG_DEBUG;
	else if (g_log_level == LOG_DEBUG)
		g_log_level = LOG_TRACE;
	else
		g_log_level = LOG_ERROR;
}

void	rt_log_ex(t_log_level lvl,
			const char *file, int line, const char *func,
			const char *fmt, ...)
{
	va_list	ap;

	if (!should_print(lvl))
		return;

	/*
	 * Simple formatting rules:
	 * - INFO/WARN/ERROR/FATAL:   "[LEVEL] message"
	 * - TRACE/DEBUG:            "[LEVEL] file:line func(): message"
	 */
	if (lvl <= LOG_DEBUG)
		fprintf(stderr, "[%s] %s:%d %s(): ", lvl_name(lvl), file, line, func);
	else
		fprintf(stderr, "[%s] ", lvl_name(lvl));

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	fputc('\n', stderr);

	if (lvl == LOG_FATAL)
		exit(EXIT_FAILURE);
}
