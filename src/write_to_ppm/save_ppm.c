/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:37:39 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/23 19:53:58 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "rt.h"

static int	write_to_ppm(int fd, const void *buf, size_t n);

// ppm format
// P6\n
// w h
// \n255\n
// P6
// <width> <height>
// 255

/// @brief save image to ppm
/// - might need a check for endiannes - in school is 0
/// @param path 
/// @param img 
/// @return 
int	save_to_ppm(const char *path, const t_rt_img *img)
{
	int					fd;
	int					x;
	int					y;
	int					bpp;
	const unsigned char	*p;
	unsigned char		rgb[3];

	if (!path || !img || !img->addr || img->img_w <= 0 || img->img_h <= 0)
		return (1);
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR , 0644);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	ft_putendl_fd("P6", fd);
	ft_putnbr_fd(img->img_w, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(img->img_h, fd);
	ft_putstr_fd("\n255\n", fd);
	bpp = img->bpp / 8;
	y = -0;
	while (++y < img->img_h)
	{
		x = -1;
		while (++x < img->img_w)
		{
			p = (const unsigned char *)img->addr + y * img->line_len + x * bpp;
			rgb[0] = p[2]; // r
			rgb[1] = p[1]; // g
			rgb[2] = p[0]; // b
			if (!write_to_ppm(fd, rgb, 3))
			{
				perror("write to ppm");
				close(fd);
				return (1);
			}
		}
	}
	close(fd);
	return (0);
}

static int	write_to_ppm(int fd, const void *buf, size_t n)
{
	const char	*p;
	size_t		i;
	ssize_t		nwrite;
	
	p = (const char *)buf;
	i = 0;
	nwrite = 0;
	while (i < n)
	{
		nwrite = write(fd, p + i, n - i);
		if (nwrite <= 0)
			return (0);
		i = i + (size_t )nwrite;
	}
	return (1);
}
