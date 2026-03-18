/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:39:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/24 11:48:48 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"
#include "libft.h"

/* 
** Description
*/
int	rt_img_create(t_rt_mlx *mlx, t_rt_img *img, int w, int h)
{
	img->ptr = mlx_new_image(mlx->mlx, w, h);
	if (!img->ptr)
		return (1);
	img->addr = (int *)mlx_get_data_addr(img->ptr,
			&img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx->mlx, img->ptr);
		img->ptr = NULL;
		return (1);
	}
	img->img_w = w;
	img->img_h = h;
	return (0);
}

/* 
** Description 
*/
void	rt_img_destroy(t_rt_mlx *rt, t_rt_img *img)
{
	if (!img)
		return ;
	if (img->ptr && rt && rt->mlx)
		mlx_destroy_image(rt->mlx, img->ptr);
	img->ptr = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->img_w = 0;
	img->img_h = 0;
}

/* 
** Description 
*/
// void	rt_img_put_pixel(t_rt_img *img, int x, int y, int color)
// {
// 	char	*pixel;
// 	int		xoffset;

// 	if (x < 0 || y < 0 || x >= img->img_w || y >= img->img_h)
// 		return ;
// 	xoffset = (y * img->line_len) + (x * (img->bpp / 8));
// 	pixel = img->addr + xoffset;
// 	*(unsigned int *)pixel = (unsigned int)color;
// }