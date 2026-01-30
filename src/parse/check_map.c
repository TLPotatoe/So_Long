/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:51:46 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/30 15:03:11 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_item(char *data, char c)
{
	int	item;
	int	index;

	item = 0;
	index = 0;
	while (data[index])
	{
		if (data[index++] == c)
			item++;
	}
	return (item);
}

int	check_map_content(t_map *map)
{
	int	index;

	index = 0;
	while (map->data[index])
	{
		if (!ft_strchr("10EPC", map->data[index++]))
		{
			write(2, "Error\nIllegal character in map.\n", 33);
			return (0);
		}
	}
	if (count_item(map->data, 'P') != 1)
		write(2, "Error\nPlayer count is incorrect.\n", 34);
	else if (count_item(map->data, 'E') != 1)
		write(2, "Error\nExit count is incorrect.\n", 32);
	else if (count_item(map->data, 'C') < 1)
		write(2, "Error\nCollectible count needs to be 1 or more.\n", 48);
	if (count_item(map->data, 'E') != 1 || count_item(map->data, 'P') != 1
		|| count_item(map->data, 'C') < 1)
		return (0);
	return (1);
}

int	check_map_fill(t_map *map)
{
	int	index;

	index = 0;
	while (map->data[index])
	{
		if (map->data[index] == 'E')
		{
			write(2, "Error\nThe exit can't be reached.\n", 34);
			return (0);
		}
		if (map->data[index] == 'C')
		{
			write(2, "Error\nAt least one collectible can't be reached.\n", 50);
			return (0);
		}
		index++;
	}
	ft_strreplace(map->data, "0", 'F');
	return (1);
}
