/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:04:47 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/23 11:42:30 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MacroLibX/includes/mlx.h"
# include "MacroLibX/includes/mlx_extended.h"
# include "libft.h"

# define MAPSIZE 500

typedef struct s_map
{
	char		*data;
	int			linelen;
}				t_map;

typedef struct s_image
{
	mlx_image	image;
	int			x;
	int			y;
	int			width;
	int			height;
}				t_image;

typedef struct s_mlx
{
	mlx_context	mlx;
	mlx_window	win;
	t_image		test_png;
}				t_mlx;

int				parse_map(char *filename, t_map map);
int				check_map_content(char *data);

void			free_buff_line(char **line, char **buff);

#endif