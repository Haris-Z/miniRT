/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:28:12 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/11 22:26:01 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // open, close, read
#include "parse.h" // EXT_RT, EXT_LEN

static bool			validate_ext(const char *path);
static t_rt_err		rt_open(const char *path, t_rt_file *out);
static t_rt_err		rt_read(const char *path, t_rt_file *out);
static void			rt_file_close(t_rt_file *f);

/**
 * @brief This function loades the scene data from an .rt file
 * 
 * adsflajölföa
 * 
 * @param argc
 * @
 * @param argv 
 * @param f 
 */
void	rt_load_file(int argc, const char *path, t_rt_file *out)
{
	t_rt_err	err;

	if (argc != 2 || !path || !out || path[0] == '\0')
	{
		rt_print_error(0, RT_ERR_USAGE, 0);
		exit(EXIT_FAILURE);
	}
	out->fd = -1;
	out->sys_errno = 0;
	err = rt_open(path, out);
	if (err != RT_SUCCESS)
	{
		rt_print_error(path, err, out);
		exit(EXIT_FAILURE);
	}
	err = rt_read(path, out);
	if (err != RT_SUCCESS)
	{
		rt_print_error(path, err, out);
		exit(EXIT_FAILURE);
	}
}

static bool	validate_ext(const char *path)
{
	const size_t	len_path = ft_strlen(path);

	if (len_path < EXT_LEN)
		return (false);
	if (ft_strncmp(path + (len_path - 3), EXT_RT, 3) != 0)
		return (false);
	return (true);
}

static t_rt_err	rt_open(const char *path, t_rt_file *out)
{
	int	fd;

	if (validate_ext(path) == false)
		return (RT_ERR_EXT);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		out->sys_errno = errno;
		return (RT_ERR_OPEN);
	}
	out->fd = fd;
	return (RT_SUCCESS);
}

static t_rt_err	rt_read(const char *path, t_rt_file *out)
{
	char	ch;
	ssize_t	bytes_read;
	int		err;

	errno = 0;
	bytes_read = read(out->fd, &ch, 1);
	if (bytes_read == -1)
	{
		err = errno;
		rt_file_close(out);
		out->sys_errno = err;
		return (RT_ERR_READ);
	}
	if (bytes_read == 0)
	{
		rt_file_close(out);
		return (RT_ERR_EMPTY);
	}
	rt_file_close(out);
	return (rt_open(path, out));
}

static void	rt_file_close(t_rt_file *f)
{
	if (!f)
		return ;
	if (f->fd >= 0)
		close(f->fd);
	f->fd = -1;
	f->sys_errno = 0;
}
