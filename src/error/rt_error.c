/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:09:01 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:22:45 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "parse.h"

int	rt_error_msg(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

const char	*rt_file_strerror(t_rt_err err)
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
// print_file_error
void	rt_print_error(const char *path, t_rt_err err, const t_rt_file *f)
{
	ft_putstr_fd(C_BOLD C_RED "Error\n" C_RESET, STDERR_FILENO);
	ft_putstr_fd(C_RESET, 2);
	ft_putstr_fd((char *)rt_file_strerror(err), STDERR_FILENO);
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

const char	*rt_parse_strerror(int err)
{
	if (err == RT_ERR_MALLOC)
		return ("Out of Memory");
	if (err == RT_ERR_TOK)
		return ("Unexpected line format");
	if (err == RT_ERR_ID)
		return ("Unknown ID");
	if (err == RT_ERR_DUP)
		return ("Duplicate Element");
	if (err == RT_ERR_FORMAT)
		return ("Invalid line format");

	if (err == RT_ERR_FORMAT_LIGHT)
		return ("Invalid line format\nExpected:\nId\tPos \
		Brightness\tColors\nL\t-40,0,30\t0.7\t\t\t255,255,255\n");
	if (err == RT_ERR_MISSING)
		return ("Missing Element Identifier - expected at least A, C, L");

	if (err == RT_ERR_BAD_INT)
		return ("Invalid integer value");
	if (err == RT_ERR_BAD_FLOAT)
		return ("Invalid float value");
	if (err == RT_ERR_RANGE_COLOR)
		return ("Color value out of range - expected [0, 255]");
	if (err == RT_ERR_URANGE)
		return ("Unit Vector out of Range: [-1,1]");
	if (err == RT_ERR_UZERO)
		return ("Unit Vector cannot be zero");
	if (err == RT_ERR_UNORM)
		return ("Unit vector must be normalized");
	if (err == RT_ERR_BAD_RATIO)
		return ("Bad float ratio - expected [0.0, 1,0]");

	if (err == RT_ERR_RANGE_FOV)
		return ("FOV out of range - expected [0, 180]");


	if (err == RT_ERR_DIAMETER)
			return ("Diameter should be bigger than 0");

	if (err == RT_ERR_HEIGHT)
			return ("Height should be bigger than 0");
	return ("Unknown error");
}

void	print_parse_err(int lineno, char *id, int err)//, int sys_errno)
{
	ft_putstr_fd(C_BOLD C_RED "Error\n" C_RESET, STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
	ft_putstr_fd("Line ", STDERR_FILENO);
	ft_putnbr_fd(lineno, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (id)
	{
		ft_putstr_fd("(", STDERR_FILENO);
		ft_putstr_fd(id, STDERR_FILENO); // eg. (A), (C), (L), (sp), (pl), (cy)
		ft_putstr_fd("): ", STDERR_FILENO);
		ft_putstr_fd(C_DIM, STDERR_FILENO);
		ft_putstr_fd((char *)rt_parse_strerror(err), STDERR_FILENO); // eg. Duplicate ID, MISSING ID, etc...
		ft_putstr_fd(C_RESET, STDERR_FILENO);
	}
	// if (sys_errno)
	// {
	// 	ft_putstr_fd(": ", STDERR_FILENO);
	// 	ft_putstr_fd(C_BOLD C_ULINE, STDERR_FILENO);
	// 	ft_putstr_fd((char *)strerror(sys_errno), STDERR_FILENO);
	// 	ft_putstr_fd(C_RESET, STDERR_FILENO);
	// }
	ft_putstr_fd("\n", STDERR_FILENO);
}
