/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:57:28 by tlamit            #+#    #+#             */
/*   Updated: 2026/02/06 21:09:17 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static float	process_scale(int i_dim, int i_size_pixel)
{
	return ((float)i_size_pixel / (float)i_dim);
}

void	scale_images(t_mlx *mlx)
{
	mlx->coin.x_scale = process_scale(mlx->coin.width, mlx->tile_size);
	mlx->coin.y_scale = process_scale(mlx->coin.height, mlx->tile_size);
	mlx->wall.x_scale = process_scale(mlx->wall.width, mlx->tile_size);
	mlx->wall.y_scale = process_scale(mlx->wall.height, mlx->tile_size);
	mlx->exit.x_scale = process_scale(mlx->exit.width, mlx->tile_size);
	mlx->exit.y_scale = process_scale(mlx->exit.height, mlx->tile_size);
	mlx->ground.x_scale = process_scale(mlx->ground.width, mlx->tile_size);
	mlx->ground.y_scale = process_scale(mlx->ground.height, mlx->tile_size);
	mlx->player.x_scale = process_scale(mlx->player.width, mlx->tile_size);
	mlx->player.y_scale = process_scale(mlx->player.height, mlx->tile_size);
}

int	load_images(t_mlx *mlx)
{
	mlx->coin.image = mlx_new_image_from_file(mlx->mlx, "images/coin.png",
			&mlx->coin.width, &mlx->coin.height);
	mlx->wall.image = mlx_new_image_from_file(mlx->mlx, "images/wall.png",
			&mlx->wall.width, &mlx->wall.height);
	mlx->exit.image = mlx_new_image_from_file(mlx->mlx, "images/exit.png",
			&mlx->exit.width, &mlx->exit.height);
	mlx->ground.image = mlx_new_image_from_file(mlx->mlx, "images/ground.png",
			&mlx->ground.width, &mlx->ground.height);
	mlx->player.image = mlx_new_image_from_file(mlx->mlx, "images/player.png",
			&mlx->player.width, &mlx->player.height);
	if (!mlx->coin.image || !mlx->wall.image || !mlx->exit.image
		|| !mlx->ground.image || !mlx->player.image)
		return (1);
	scale_images(mlx);
	return (0);
}

void	window_size(t_mlx *mlx, mlx_window_create_info *info)
{
	float	rescale_x;
	float	rescale_y;

	rescale_x = (float)mlx->map->linelen * (float)mlx->tile_size
		/ (float)info->width;
	rescale_y = (float)ft_strlen(mlx->map->data) / (float)mlx->map->linelen
		* (float)mlx->tile_size / (float)info->height;
	if (rescale_x > rescale_y)
		mlx->tile_size /= rescale_x;
	else
		mlx->tile_size /= rescale_y;
	info->width = mlx->map->linelen * mlx->tile_size;
	info->height = ft_strlen(mlx->map->data) / mlx->map->linelen
		* (float)mlx->tile_size;
}
