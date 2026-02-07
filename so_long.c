/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:24:56 by tlamit            #+#    #+#             */
/*   Updated: 2026/02/07 01:49:06 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	check_file_name(char *filename)
{
	char	*end;
	int		len;

	end = ft_strrchr(filename, '.');
	if (!end)
		return (1);
	len = ft_strlen(filename + (end - filename));
	if (len != 4)
		return (1);
	if (ft_strncmp(filename + (end - filename), ".ber", 3))
		return (1);
	return (0);
}

static int	map_init(char *filename, t_map *map)
{
	int	result;

	result = parse_map(filename, map);
	if (result)
	{
		if (result != 2)
			free(map->data);
		return (1);
	}
	if (check_map_content(map))
	{
		free(map->data);
		return (1);
	}
	flood(map);
	if (!check_map_fill(map))
	{
		free(map->data);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	static t_map	map = {0};

	if (ac != 2)
	{
		write(2, "Error\n./so_long <map>.ber\n", 27);
		return (0);
	}
	if (ft_strlen(av[1]) < 5)
	{
		write(2, "Error\nInvalid file name.\n", 26);
		return (0);
	}
	if (check_file_name(av[1]))
	{
		write(2, "Error\nInvalid file extension.\n", 31);
		return (0);
	}
	if (map_init(av[1], &map))
		return (0);
	map.previous_slot = 0;
	game(&map);
	free(map.data);
}
