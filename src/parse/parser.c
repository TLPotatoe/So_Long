/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:37:31 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/20 14:14:52 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static int	map_len(char *filename)
// {
// 	int		fd;
// 	int		len;
// 	char	*line;
// 	size_t	prev_len;

// 	len = 0;
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	prev_len = 2147483648;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		ft_printf("GNL LEN %d PREV %d\n", ft_strlen(line), prev_len);
// 		if (!line || (ft_strlen(line) != prev_len && prev_len != 2147483648))
// 		{
// 			close(fd);
// 			return (len);
// 		}
// 		prev_len = ft_strlen(line);
// 		len += prev_len - 1;
// 		free(line);
// 	}
// 	close(fd);
// 	return (len);
// }

// int	*parse_map(char *filename)
// {
// 	int	i;
// 	int	fd;
// 	int	len;
// 	int	*map;

// 	len = map_len(filename);
// 	if (!len)
// 		return (NULL);
// 	map = malloc(sizeof(char *) * (len + 1));
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (NULL);
// 	i = 0;
// 	while (1)
// 	{
// 		len = read(fd, &(map[i++]), 1);
// 	}
// 	return (NULL);
// }

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
		buffer = malloc(17);
		if (!buffer)
			free_buff_line(&line, &buffer);
		len = read(fd, buffer, 16);
		if (!len)
			break ;
		buffer[len] = 0;
		line = gnl_ft_strjoin(line, buffer);
	}
	free(buffer);
	close(fd);
	return (line);
}

char	*parse_map(char *filename)
{
	char *raw;

	raw = get_raw_file(filename);
	ft_printf("%s\n", raw);
	free(raw);

	return (NULL);
}