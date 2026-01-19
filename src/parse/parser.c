/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:37:31 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/19 19:04:46 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	map_len(char *filename)
{
	int		fd;
	int		len;
	char	*line;

	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (0);
		}
		len += ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
	return (len);
}

int	*parse_map(char *filename)
{
	int		fd;
	int		len;
	int		*map;
	char	*line;

	len = map_len(filename);
	if (!len)
		return (NULL);
	map = malloc(sizeof(int) * len);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		free(line);
	}
	return (NULL);
}
