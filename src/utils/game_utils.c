/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:02:36 by tlamit            #+#    #+#             */
/*   Updated: 2026/02/06 20:07:34 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	level_finished(t_mlx *mlx)
{
	if (!ft_strchr(mlx->map->data, 'T') && !ft_strchr(mlx->map->data, 'S'))
		mlx_loop_end(mlx->mlx);
}

void	put_transformed_image(t_mlx *mlx, t_image *image, int index, int state)
{
	int	x;
	int	y;
	int	transform;

	x = index % mlx->map->linelen * mlx->tile_size;
	y = index / mlx->map->linelen * mlx->tile_size;
	transform = 1;
	if (state)
	{
		x = (index + 1) % mlx->map->linelen * mlx->tile_size;
		transform = -1;
	}
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win, image->image, x, y,
		image->x_scale * transform, image->y_scale, 0.0f);
}

void	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (event == 0)
		mlx_loop_end(mlx->mlx);
}
