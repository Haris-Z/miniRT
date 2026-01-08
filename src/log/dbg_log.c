/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:24:07 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 22:28:51 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

void	debug_log_impl(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}
