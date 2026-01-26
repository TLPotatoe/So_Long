/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:51:46 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/26 18:55:26 by tlamit           ###   ########.fr       */
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
			return (0);
	}
	if (count_item(map->data, 'P') != 1 || count_item(map->data, 'E') != 1
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
		if (ft_strchr("0EC", map->data[index++]))
			return (0);
	}
	if (count_item(map->data, '0') != 0 || count_item(map->data, 'C') != 0
		|| count_item(map->data, 'E') != 0)
		return (0);
	return (1);
}
