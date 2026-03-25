/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:37:39 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/25 20:33:48 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "mrt.h"

// ppm format
// P6\n
// w h
// \n255\n
// P6
// <width> <height>
// 255
static void	write_ppm_header(int width, int height, int fd)
{
	ft_putendl_fd("P6", fd);
	ft_putnbr_fd(width, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(height, fd);
	ft_putstr_fd("\n255\n", fd);
}

static int	write_to_ppm(int fd, const void *buf, size_t n);

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
	// [ factor out to extra func --> create_file_path() from here
	char				buf[512];
	char				*start;
	char				*usec;
	struct timeval		tv;
	
	buf[0] = '\0';
	ft_strlcat(buf, "saved_images/", sizeof buf);
	start = ft_strrchr(path, '/') + 1;
	ft_strlcat(buf, start,  ft_strlen((char *)buf) + ft_strlen(start) - ft_strlen(".rt") + 1);
	ft_strlcat(buf, "_", sizeof buf);
	gettimeofday(&tv, NULL);
	usec = ft_itoa((int)tv.tv_usec / 1000);
	if (!usec)
	{
		perror("usec");
		return (1);
	}
	ft_strlcat(buf, usec, sizeof buf);
	free(usec);
	ft_strlcat(buf, ".ppm", sizeof buf);
	// to here ]

	fd = open((const char *)buf, O_CREAT | O_TRUNC | O_RDWR , 0644); //-rw-r--r--
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	write_ppm_header(img->img_w, img->img_h, fd);
	// [ factor out from here -- > func_name()
	bpp = img->bpp / 8;
	y = -1;
	while (++y < img->img_h)
	{
		x = -1;
		while (++x < img->img_w)
		{
			p = (const unsigned char *)img->addr + y * img->line_len + x * bpp;
			rgb[0] = p[2]; // r
			rgb[1] = p[1]; // g
			rgb[2] = p[0]; // b
			// rgb[0] = p[0]; // r
			// rgb[1] = p[1]; // g
			// rgb[2] = p[2]; // b
			if (!write_to_ppm(fd, rgb, 3))
			{
				perror("write to ppm");
				close(fd);
				return (1);
			}
		}
	}
	// ] to here
	close(fd);
	ft_putstr_fd("created: ", 1);
	ft_putendl_fd((char *)buf, 1);
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
