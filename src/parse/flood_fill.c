/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:36:40 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/26 19:19:22 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	replace(t_map *map, int index, char seek, char replace)
{
	if (!map->data[index])
		return (0);
	if (map->data[index] == seek)
	{
		map->data[index] = replace;
		return (1);
	}
	return (0);
}

static int	fill_around(t_map *map, int index)
{
	int	count;

	count = 0;
	count += replace(map, index - map->linelen, '0', 'F');
	count += replace(map, index + map->linelen, '0', 'F');
	count += replace(map, index - 1, '0', 'F');
	count += replace(map, index + 1, '0', 'F');
	count += replace(map, index - map->linelen, 'C', 'T');
	count += replace(map, index + map->linelen, 'C', 'T');
	count += replace(map, index - 1, 'C', 'T');
	count += replace(map, index + 1, 'C', 'T');
	count += replace(map, index - map->linelen, 'E', 'S');
	count += replace(map, index + map->linelen, 'E', 'S');
	count += replace(map, index - 1, 'E', 'S');
	count += replace(map, index + 1, 'E', 'S');
	return (count);
}

static int	fill(t_map *map, int index)
{
	if (ft_strchr("PFTS", map->data[index]))
		return (fill_around(map, index));
	return (0);
}

int	flood(t_map *map)
{
	size_t	index;
	int		count;

	index = 0;
	count = 1;
	while (count)
	{
		count = 0;
		index = map->linelen;
		while (index < ft_strlen(map->data) - map->linelen)
		{
			count += fill(map, index);
			index++;
		}
	}
	// index = 0;
	// while (index < ft_strlen(map->data))
	// {
	// 	if (index % map->linelen == 0)
	// 		ft_printf("\n");
	// 	ft_printf("%c", map->data[index]);
	// 	index++;
	// }
	return (1);
}
