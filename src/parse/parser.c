/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:37:31 by tlamit            #+#    #+#             */
/*   Updated: 2026/02/05 16:57:05 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*get_raw_file(char *filename)
{
	int		fd;
	int		len;
	char	*line;
	char	*buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		write(2, "Error:\nUnable to read file.\n", 29);
	if (fd < 2)
		return ((char *)1);
	line = NULL;
	while (1)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			free_buff_line(&line, &buffer);
		len = read(fd, buffer, BUFFER_SIZE);
		if (!len)
			break ;
		buffer[len] = 0;
		line = gnl_ft_strjoin(line, buffer);
	}
	free(buffer);
	close(fd);
	return (line);
}

static int	check_global_len(char *data)
{
	int	index;
	int	len;
	int	count;

	index = 0;
	len = 0;
	while (data[index] && data[index] != '\n')
		index++;
	len = index++;
	index = 0;
	count = 0;
	while (data[index])
	{
		if (data[index] == '\n' && count != len)
			return (1);
		if (data[index] != '\n')
			count++;
		else
			count = 0;
		index++;
	}
	index = 0;
	return (0);
}

static int	check_border(char *data, int len, int line_len)
{
	int	index;

	if (check_global_len(data))
		return (1);
	ft_remchr(data, "\n");
	index = 0;
	while (index < len)
	{
		if ((index / line_len == 0 || (index / line_len) + 1 == len / line_len)
			&& data[index] != '1')
			return (1);
		if ((index % line_len == 0 || index % line_len == line_len - 1)
			&& data[index] != '1')
			return (1);
		index++;
	}
	return (0);
}

static int	check_map(char *data)
{
	int	len;
	int	index;
	int	linelen;

	len = 0;
	index = -1;
	linelen = 0;
	while (data[++index])
	{
		if (data[index] == '\n' && !linelen)
			linelen = index;
		if (data[index] != '\n')
			len++;
	}
	if (!linelen || len % linelen != 0)
	{
		write(2, "Error:\nMap size not rectangular.\n", 34);
		return (-1);
	}
	if (check_border(data, len, linelen))
	{
		write(2, "Error:\nMap border incorrect.\n", 30);
		return (-1);
	}
	return (linelen);
}

int	parse_map(char *filename, t_map *map)
{
	map->data = get_raw_file(filename);
	if (!map->data)
	{
		write(2, "Error:\nEmpty file.\n", 20);
		return (1);
	}
	if (map->data == (char *)1)
		return (2);
	map->linelen = check_map(map->data);
	if (map->linelen == -1)
		return (1);
	if (map->linelen < 3 || ft_strlen(map->data) / map->linelen < 3)
	{
		write(2, "Error\nMap needs to be at least 3 collums and 3 rows.\n", 54);
		return (1);
	}
	if (map->linelen > 50 || ft_strlen(map->data) / map->linelen > 50)
	{
		write(2, "Error\nMap needs to be at most 50 collums and 50 rows.\n",
			55);
		return (1);
	}
	return (0);
}
