/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_log.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:24:46 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 18:45:57 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBG_LOG_H
# define DBG_LOH_H

# include <stddef.h>
# include <sys/types.h>

/**
 * @brief 
 * 
 * @param fmt 
 * @param ... 
 */
void	debug_log_impl(const char *fmt, ...);

# ifdef RT_DEBUG
#  define debug_log(...) debug_log_impl(__VA_ARGS__)
# else
#  define debug_log(...) ((void)0)
# endif

#endif
