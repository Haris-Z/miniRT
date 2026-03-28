/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:27:23 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/28 23:13:00 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "rt_error.h"
#include "parse.h"

static const char	*parse_strerror(int err);
static const char	*format_strerror(int err);
static const char	*rt_strerror(int err);

void	print_parse_err(int lineno, char *id, int err, char *line)
{
	ft_putstr_fd(C_BOLD C_RED "Error\n" C_RESET, STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
	ft_putstr_fd("Line ", STDERR_FILENO);
	ft_putnbr_fd(lineno, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (id)
	{
		ft_putstr_fd("(", STDERR_FILENO);
		ft_putstr_fd(id, STDERR_FILENO);
		ft_putstr_fd("): ", STDERR_FILENO);
		ft_putstr_fd(C_DIM, STDERR_FILENO);
		ft_putstr_fd((char *)rt_strerror(err), STDERR_FILENO);
		if (err == RT_ERR_LIGHT_COUNT)
		{
			ft_putstr_fd(" | MAX_LIGHTS: ", STDERR_FILENO);
			ft_putnbr_fd(MAX_LIGHTS, STDERR_FILENO);
		}
		ft_putstr_fd(C_RESET, STDERR_FILENO);
	}
	if (line)
	{
		ft_putstr_fd("--> ", STDERR_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

static const char	*format_strerror(int err)
{
	if (err == RT_ERR_TOK)
		return ("Unexpected line format");
	if (err == RT_ERR_ID)
		return ("Unknown ID");
	if (err == RT_ERR_DUP)
		return ("Duplicate Element");
	if (err == RT_ERR_LIGHT_COUNT)
		return ("Too many lights");
	if (err == RT_ERR_MISSING)
		return ("Missing Element Identifier - expected at least A, C, L");
	if (err == RT_ERR_FORMAT)
		return ("Invalid line format");
	if (err == RT_ERR_FORMAT_LIGHT)
		return ("Invalid line format\nExpected:\nId\tPos \
		Brightness\tColors\nL\t-40,0,30\t0.7\t\t\t255,255,255\n");
	if (err == RT_ERR_FORMAT_CAM)
		return ("Invalid line format\nExpected:\nId\tPosition \
			Direction\tFOV(in deg)\nC\t0,-1,3\t\t\t\t0,0,-1\t\t70\n");
	if (err == RT_ERROR_FORMAT_AMBIENT)
		return ("Invalid line format\nExpected:\nId\tRatio\tColors \
			\nA\t0.2\t\t255,255,255\n");
	return ("Unknown format error");
}

static const char	*parse_strerror(int err)
{
	if (err == RT_ERR_BAD_INT)
		return ("Invalid integer value");
	if (err == RT_ERR_BAD_FLOAT)
		return ("Invalid float value");
	if (err == RT_ERR_BAD_RATIO)
		return ("Bad float ratio - expected [0.0, 1,0]");
	if (err == RT_ERR_URANGE)
		return ("Unit Vector out of Range: [-1,1]");
	if (err == RT_ERR_RANGE_COLOR)
		return ("Color value out of range - expected [0, 255]");
	if (err == RT_ERR_UZERO)
		return ("Unit Vector cannot be zero");
	if (err == RT_ERR_UNORM)
		return ("Unit vector must be normalized");
	if (err == RT_ERR_RANGE_FOV)
		return ("FOV out of range - expected [0, 180]");
	if (err == RT_ERR_DIAMETER)
		return ("Diameter should be bigger than 0");
	if (err == RT_ERR_HEIGHT)
		return ("Height should be bigger than 0");
	if (err == RT_ERR_TEX)
		return ("Invalid texture");
	return ("Unknown parse error");
}

static const char	*rt_strerror(int err)
{
	if (err == RT_ERR_MALLOC)
		return ("Out of Memory");
	if (err >= RT_ERR_TOK && err <= RT_ERROR_FORMAT_AMBIENT)
		return (format_strerror(err));
	if (err >= RT_ERR_BAD_INT && err <= RT_ERR_TEX)
		return (parse_strerror(err));
	return ("Unknown rt error");
}
