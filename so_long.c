/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:24:56 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/27 18:18:06 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	check_file_name(char *filename)
{
	char	*end;
	int		len;

	end = ft_strrchr(filename, '.');
	if (!end)
		return (0);
	if (ft_strlen(filename) <= 4)
		return (0);
	len = ft_strlen(filename + (end - filename));
	if (len != 4)
		return (0);
	if (ft_strncmp(filename + (end - filename), ".ber", 3))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	static t_map	map = {0};

	if (ac != 2)
		return (0);
	if (!check_file_name(av[1]))
		return (0);
	if (parse_map(av[1], &map))
		return (0);
	flood(&map);
	if (!check_map_fill(&map))
	{
		free(map.data);
		return (0);
	}
	map.previous_slot = 0;
	game(&map);
	free(map.data);
}
