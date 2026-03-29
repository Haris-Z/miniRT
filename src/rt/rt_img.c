/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:39:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/29 18:47:53 by agara            ###   ########.fr       */
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
