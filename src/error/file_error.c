/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:10:57 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/28 23:13:22 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "parse.h"

static const char	*file_strerror(t_rt_err err);

void	print_file_err(const char *path, t_rt_err err, const t_rt_file *f)
{
	ft_putstr_fd(C_BOLD C_RED "Error\n" C_RESET, STDERR_FILENO);
	ft_putstr_fd(C_RESET, 2);
	ft_putstr_fd((char *)file_strerror(err), STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd(": --> [", STDERR_FILENO);
		ft_putstr_fd(C_DIM, STDERR_FILENO);
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(C_RESET, STDERR_FILENO);
		ft_putstr_fd("]", STDERR_FILENO);
	}
	if (f && f->sys_errno != 0)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(C_BOLD C_ULINE, STDERR_FILENO);
		ft_putstr_fd((char *)strerror(f->sys_errno), STDERR_FILENO);
		ft_putstr_fd(C_RESET, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

static const char	*file_strerror(t_rt_err err)
{
	if (err == RT_ERR_ARG)
		return ("Invalid argument");
	if (err == RT_ERR_USAGE)
		return ("Usage: ./miniRT < file_name.rt >");
	if (err == RT_ERR_EXT)
		return ("File extension must be [ .rt ]");
	if (err == RT_ERR_OPEN)
		return ("Can't open file");
	if (err == RT_ERR_READ)
		return ("Can't read file");
	if (err == RT_ERR_EMPTY)
		return ("File is empty");
	if (err == RT_ERR_MALLOC)
		return ("Out of Memory");
	return ("Unknown error");
}
