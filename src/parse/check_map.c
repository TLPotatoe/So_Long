/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:51:46 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/23 13:49:49 by tlamit           ###   ########.fr       */
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
		if (data[index++] == c)
			item++;
	return (item);
}

int	check_map_content(char *data)
{
	int	index;

	index = 0;
	while (data[index])
		if (ft_strchr("10EPC", data[index++]) == NULL)
			return (0);
	if (count_item(data, 'P'))
		return (1);
	return (1);
}
