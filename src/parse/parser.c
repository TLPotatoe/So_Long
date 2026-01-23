/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:37:31 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/23 11:48:40 by tlamit           ###   ########.fr       */
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
		return (NULL);
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

	index = 0;
	len = 0;
	while (data[index] && data[index] != '\n')
	{
		len++;
		index++;
	}
	index = 0;
	return (0);
}

static int	check_border(char *data, int len, int line_len)
{
	int	index;

	if (check_global_len(*data))
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
	index = 0;
	linelen = 0;
	while (data[index])
	{
		if (data[index] == '\n' && !linelen)
			linelen = index;
		if (data[index] != '\n')
			len++;
		index++;
	}
	if (len % linelen != 0)
		return (0);
	return (!check_border(data, len, linelen) * linelen);
}

int	parse_map(char *filename, t_map map)
{
	map.data = get_raw_file(filename);
	map.linelen = check_map(map.data);
	ft_printf("\nLEN STATUS %d\n", map.linelen);
	if (map.linelen == 0)
	{
		free(map.data);
		return (1);
	}
	ft_printf("\nMAP STATUS %d\n", check_map_content(map.data));
	return (0);
}
