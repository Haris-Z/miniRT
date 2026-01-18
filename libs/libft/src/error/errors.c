/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:29:28 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/17 13:40:48 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <errno.h>
//#include <string.h>
#include "libft.h"

void	print_error_builtins(char *cmd, const char *arg, char *error)
{
	ft_putendl_fd("Error:", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd((char *)arg, STDERR_FILENO);
	}
	if (arg)
		ft_putstr_fd(" ", STDERR_FILENO);
	else
		ft_putstr_fd(":", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}

void	debug(char *file, const char *func, int line, char *arg)
{
	printf("%s: %d:  %s: | %s\n", file, line, func, arg);
}

void	report_error(const char *context, const char *message)
{
	if (context)
		ft_putstr_fd((char *)context, STDERR_FILENO);
	if (message)
		ft_putendl_fd((char *)message, STDERR_FILENO);
	else
		ft_putendl_fd("Error", STDERR_FILENO);
}

int	handle_memory_error(void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	report_error(NULL, "strerror(ENOMEM)");
	return (1);
}

int	handle_system_error(void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	report_error(NULL, "strerror(errno)");
	return (1);
}

void	*ft_malloc(size_t size, const char *context)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		report_error(context, "strerror(ENOMEM)");
		return (NULL);
	}
	return (ptr);
}
