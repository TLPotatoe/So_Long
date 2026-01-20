/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:24:56 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/20 16:40:06 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file(char *filename)
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
	char	*map;

	if (ac != 2)
		return (0);
	if (!check_file(av[1]))
		return (0);
	map = parse_map(av[1]);
	if (!map)
		return (0);
	free(map);
}
