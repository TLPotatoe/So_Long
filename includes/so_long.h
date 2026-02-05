/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:04:47 by tlamit            #+#    #+#             */
/*   Updated: 2026/02/05 13:53:39 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"
# include "mlx_extended.h"

typedef struct s_map
{
	char		*data;
	int			linelen;
	char		previous_slot;
}				t_map;

typedef struct s_image
{
	mlx_image	image;
	int			width;
	int			height;
}				t_image;

typedef struct s_mlx
{
	mlx_context	mlx;
	mlx_window	win;
	t_map		*map;
	t_image		wall;
	t_image		coin;
	t_image		exit;
	t_image		ground;
	t_image		player;
	int			player_direction;
	int			tile_size;
}				t_mlx;

void			game(t_map *map);
int				load_images(t_mlx *mlx);
void			level_finished(t_mlx *mlx);
void			window_hook(int event, void *param);
void			put_transformed_image(t_mlx *mlx, t_image *image, int index,
					int state);

int				flood(t_map *map);
int				check_map_fill(t_map *map);
int				check_map_content(t_map *map);
int				parse_map(char *filename, t_map *map);

void			up(t_map *map, int *i);
void			down(t_map *map, int *i);
void			right(t_map *map, int *i);
void			left(t_map *map, int *i);

void			free_buff_line(char **line, char **buff);

#endif
