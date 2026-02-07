/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:03:57 by tlamit            #+#    #+#             */
/*   Updated: 2026/02/07 01:46:25 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	tile_draw(t_mlx *mlx, t_image *image, int index)
{
	if (image->image == mlx->player.image || image->image == mlx->coin.image
		|| image->image == mlx->exit.image)
		put_transformed_image(mlx, &mlx->ground, index, 0);
	if (image->image == mlx->player.image)
	{
		put_transformed_image(mlx, &mlx->player, index, mlx->player_direction);
		return ;
	}
	if (image->image == mlx->exit.image && ft_strchr(mlx->map->data, 'T'))
		return ;
	put_transformed_image(mlx, image, index, 0);
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
			tile_draw(mlx, &mlx->ground, index);
		if (mlx->map->data[index] == 'T')
			tile_draw(mlx, &mlx->coin, index);
		if (mlx->map->data[index] == 'S')
			tile_draw(mlx, &mlx->exit, index);
		if (mlx->map->data[index] == 'P')
			tile_draw(mlx, &mlx->player, index);
		index++;
	}
}

void	game(t_map *map)
{
	t_mlx							mlx;
	static mlx_window_create_info	info = {0};

	info.width = 1920;
	info.height = 1000;
	info.title = "so_long";
	info.is_resizable = false;
	mlx.map = map;
	mlx.tile_size = 500;
	mlx.player_direction = 0;
	window_size(&mlx, &info);
	scale_images(&mlx);
	mlx.mlx = mlx_init();
	if (load_images(&mlx))
		return ;
	mlx.win = mlx_new_window(mlx.mlx, &info);
	mlx_set_fps_goal(mlx.mlx, 60);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
	mlx_add_loop_hook(mlx.mlx, update, &mlx);
	mlx_loop(mlx.mlx);
	return ;
}
