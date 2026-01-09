/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_log.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:30:51 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/09 15:49:58 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACELOG_H
# define TRACELOG_H

# include <stdarg.h>

// see raylib
typedef enum e_log_level
{
	LOG_ALL = 0,	/* print everything */
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL,
	LOG_NONE		/* print nothing */
}	t_log_level;

/* configure */

// set rt_log_set_level() to the loglevel at the beginning of main or wherever you want to use it
void		rt_log_set_level(t_log_level lvl);
t_log_level	rt_log_get_level(void);
void		rt_log_cycle_level(void);

void		rt_log_ex(t_log_level lvl,
				const char *file, int line, const char *func,
				const char *fmt, ...);

# ifdef RT_DEBUG
#  define TRACELOG(_lvl, ...) \
	do \
		{ \
			rt_log_ex((_lvl), __FILE__, __LINE__, __func__, __VA_ARGS__); \
		} \
		while (0)
# else
#  define TRACELOG(_lvl, ...) \
	do \
		{ \
			(void)(_lvl); \
		} while (0)
# endif // RT_DEBUG
	
#endif // TRACELOG_H
