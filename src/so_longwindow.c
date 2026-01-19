/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:03:57 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/19 16:30:23 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int size = 200;

void	key_hook(int key, void *param)
{
	int		x;
	int		y;
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_mouse_get_pos(mlx->mlx, &x, &y);
	if (key == 41) // ESCAPE
		mlx_loop_end(mlx->mlx);
	else if (key == 22) // (S)how
		mlx_mouse_show(mlx->mlx);
	else if (key == 11) // (H)ide
		mlx_mouse_hide(mlx->mlx);
	else if (key == 6) // (C)lear
		mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0xFFFFFFFF});
	else if (key == 79) // RIGHT KEY
		mlx->test_png.x += (float)mlx->test_png.width * (float)size/(float)mlx->test_png.width;
	else if (key == 80) // LEFT KEY
		mlx->test_png.x -= (float)mlx->test_png.width * (float)size/(float)mlx->test_png.width;
	else if (key == 81) // UP KEY
		mlx->test_png.y += (float)mlx->test_png.height * (float)size/(float)mlx->test_png.height;
	else if (key == 82) // DOWN KEY
		mlx->test_png.y -= (float)mlx->test_png.height * (float)size/(float)mlx->test_png.height;
	// mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){ .rgba = 0x000000FF });
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win, mlx->test_png.image, mlx->test_png.x, mlx->test_png.y, (float)size/(float)mlx->test_png.width, (float)size/(float)mlx->test_png.height, 0.0f);
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(((t_mlx *)param)->mlx);
}

int	main(void)
{
	t_mlx					mlx;
	static mlx_window_create_info	info = { 0 };

	info.title = "so_long";
	info.width = 1000;
	info.height = 1000;
	info.is_resizable = false;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, &info);
	mlx_set_fps_goal(mlx.mlx, 60);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
	mlx.test_png.image = mlx_new_image_from_file(mlx.mlx, "images/grass.png", &mlx.test_png.width, &mlx.test_png.height);
	mlx.test_png.x = 0;
	mlx.test_png.y = 0;
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.test_png.image, 0, 0);
	//mlx_add_loop_hook(mlx.mlx, update, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
