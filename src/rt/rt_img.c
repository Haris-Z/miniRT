/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:39:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/08 17:05:29 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* 
** Description 
*/
int	rt_img_create(t_rt_mlx *rt, t_img *img, int w, int h)
{
	img->ptr = mlx_new_image(rt->mlx, w, h);
	if (!img->ptr)
		return (E_RT_IMG_CREATE);//(E_RT_IMG_CREATE);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(rt->mlx, img->ptr);
		img->ptr = NULL;
		return (E_RT_IMG_CREATE);//(E_RT_IMG_CREATE);
	}
	img->img_w = w;
	img->img_h = h;
	return (0);
}

/* 
** Description 
*/
void	rt_img_destroy(t_rt_mlx *rt, t_img *img)
{
	if (img->ptr)
		mlx_destroy_image(rt->mlx, img->ptr);
	img->ptr = NULL;
	img->addr = NULL;
}

/* 
** Description 
*/
void	rt_img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst; //(unsigned char *)
	int		offset;

	if (x < 0 || y < 0 || x >= img->img_w || y >= img->img_h)
		return ;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = (unsigned int)color;
}