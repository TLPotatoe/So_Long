/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:03:57 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/27 17:25:32 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MacroLibX/includes/mlx.h"
#include "MacroLibX/includes/mlx_extended.h"
#include "so_long.h"
#include <math.h>
#include <stdio.h>

static float	process_scale(int i_dim, int i_size_pixel)
{
	return ((float)i_size_pixel / (float)i_dim);
}

void	level_finished(t_mlx *mlx)
{
	if (!ft_strchr(mlx->map->data, 'T') && !ft_strchr(mlx->map->data, 'S'))
		mlx_loop_end(mlx->mlx);
}

void	key_hook(int key, void *param)
{
	static int	i = 0;
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	else if (key == 79)
	{
		right(mlx->map, &i);
		mlx->player_direction = 1;
	}
	else if (key == 80)
	{
		left(mlx->map, &i);
		mlx->player_direction = 0;
	}
	else if (key == 81)
		down(mlx->map, &i);
	else if (key == 82)
		up(mlx->map, &i);
	level_finished(mlx);
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

void	tile_draw(t_mlx *mlx, t_image *image, int index)
{
	if (image->image == mlx->player.image || image->image == mlx->coin.image
		|| image->image == mlx->exit.image)
		put_transformed_image(mlx, &mlx->grass, index, 0);
	if (image->image == mlx->player.image)
	{
		put_transformed_image(mlx, &mlx->player, index, mlx->player_direction);
		return ;
	}
	put_transformed_image(mlx, image, index, 0);
}

void	update(void *param)
{
	t_mlx	*mlx;
	int		index;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0x000000FF});
	index = 0;
	while (mlx->map->data[index])
	{
		if (mlx->map->data[index] == '1')
			tile_draw(mlx, &mlx->wall, index);
		if (mlx->map->data[index] == 'F')
			tile_draw(mlx, &mlx->grass, index);
		if (mlx->map->data[index] == 'T')
			tile_draw(mlx, &mlx->coin, index);
		if (mlx->map->data[index] == 'S')
			tile_draw(mlx, &mlx->exit, index);
		if (mlx->map->data[index] == 'P')
			tile_draw(mlx, &mlx->player, index);
		index++;
	}
}

// void	window_size(t_mlx *mlx, mlx_window_create_info info)
// {
// }

void	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (event == 0)
		mlx_loop_end(mlx->mlx);
}

int	game(t_map *map)
{
	t_mlx							mlx;
	static mlx_window_create_info	info = {0};

	info.title = "so_long";
	mlx.tile_size = 50;
	mlx.player_direction = 0;
	info.width = 1900;
	info.height = 1000;
	info.is_resizable = false;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, &info);
	mlx_set_fps_goal(mlx.mlx, 60);
	mlx.coin.image = mlx_new_image_from_file(mlx.mlx, "images/coin.png",
			&mlx.coin.width, &mlx.coin.height);
	mlx.wall.image = mlx_new_image_from_file(mlx.mlx, "images/wall.png",
			&mlx.wall.width, &mlx.wall.height);
	mlx.exit.image = mlx_new_image_from_file(mlx.mlx, "images/exit.png",
			&mlx.exit.width, &mlx.exit.height);
	mlx.grass.image = mlx_new_image_from_file(mlx.mlx, "images/grass.png",
			&mlx.grass.width, &mlx.grass.height);
	mlx.player.image = mlx_new_image_from_file(mlx.mlx, "images/player.png",
			&mlx.player.width, &mlx.player.height);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
	mlx.map = map;
	mlx_add_loop_hook(mlx.mlx, update, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
