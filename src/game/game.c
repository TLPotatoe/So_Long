/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:03:57 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/27 16:14:48 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MacroLibX/includes/mlx.h"
#include "MacroLibX/includes/mlx_extended.h"
#include "so_long.h"
#include <math.h>
#include <stdio.h>

// int			size = 200;

// static int	process_scale(int dim, int size, int i_scale)
// {
// 	return ((float)dim * (float)size / (float)i_scale);
// }

static float	process_scale(int i_dim, int i_size_pixel)
{
	return ((float)i_size_pixel / (float)i_dim);
}

void	key_hook(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	else if (key == 79)
		right(mlx->map);
	else if (key == 80)
		left(mlx->map);
	else if (key == 81)
		up(mlx->map);
	else if (key == 82)
		down(mlx->map);
	// mlx_mouse_get_pos(mlx->mlx, &x, &y);
	// mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0x000000FF});
	// mlx_put_transformed_image_to_window(mlx->mlx, mlx->win,
	// mlx->test_png.image,
	// mlx->test_png.x, mlx->test_png.y, (float)size
	// / (float)&mlx->test_png.width, (float)size / (float)mlx->test_png.height,
	// 0.0f);
}

void	put_transformed_image(t_mlx *mlx, t_image *image, int index)
{
	int	x;
	int	y;

	x = index % mlx->map->linelen * mlx->tile_size;
	y = index / mlx->map->linelen * mlx->tile_size;
	if (image->image == mlx->player.image || image->image == mlx->coin.image
		|| image->image == mlx->exit.image)
	{
		mlx_put_transformed_image_to_window(mlx->mlx, mlx->win,
			mlx->grass.image, x, y, process_scale(mlx->grass.width,
				mlx->tile_size), process_scale(mlx->grass.width,
				mlx->tile_size), 0.0f);
	}
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win, image->image, x, y,
		process_scale(image->width, mlx->tile_size), process_scale(image->width,
			mlx->tile_size), 0.0f);
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
			put_transformed_image(mlx, &mlx->wall, index);
		if (mlx->map->data[index] == 'F')
			put_transformed_image(mlx, &mlx->grass, index);
		if (mlx->map->data[index] == 'T')
			put_transformed_image(mlx, &mlx->coin, index);
		if (mlx->map->data[index] == 'S')
			put_transformed_image(mlx, &mlx->exit, index);
		if (mlx->map->data[index] == 'P')
			put_transformed_image(mlx, &mlx->player, index);
		index++;
	}
}

// void	window_size(t_mlx *mlx, mlx_window_create_info info)
// {
// 	(void)mlx, info;
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
	mlx.tile_size = 100;
	info.width = 1920;
	info.height = 1080;
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
