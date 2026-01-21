/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:37:31 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/21 15:17:27 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_buff_line(char **line, char **buff)
{
	free(*line);
	free(*buff);
}

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

static int	check_border(char *data, int len, int ll)
{
	int	index;

	index = 0;
	while (index < len)
	{
		if ((index / ll == 0 || (index / ll) + 1 == len / ll)
			&& data[index] != '1')
			return (1);
		if ((index % ll == 0 || index % ll == ll - 1) && data[index] != '1')
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
	ft_remchr(data, "\n");
	return (check_border(data, len, linelen));
}

char	*parse_map(char *filename)
{
	char	*raw;

	raw = get_raw_file(filename);
	ft_printf("\n%d\n", check_map(raw));
	return (raw);
}
