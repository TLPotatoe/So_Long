/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:02:36 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/28 14:04:29 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static float	process_scale(int i_dim, int i_size_pixel)
{
	return ((float)i_size_pixel / (float)i_dim);
}

void	level_finished(t_mlx *mlx)
{
	if (!ft_strchr(mlx->map->data, 'T') && !ft_strchr(mlx->map->data, 'S'))
		mlx_loop_end(mlx->mlx);
}

void	put_transformed_image(t_mlx *mlx, t_image *image, int index, int state)
{
	int		x;
	int		y;
	float	scale_x;
	float	scale_y;

	x = index % mlx->map->linelen * mlx->tile_size;
	y = index / mlx->map->linelen * mlx->tile_size;
	scale_x = process_scale(image->width, mlx->tile_size);
	scale_y = process_scale(image->height, mlx->tile_size);
	if (state)
	{
		x = (index + 1) % mlx->map->linelen * mlx->tile_size;
		scale_x *= -1;
	}
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win, image->image, x, y,
		scale_x, scale_y, 0.0f);
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
	return (0);
}

void	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (event == 0)
		mlx_loop_end(mlx->mlx);
}
