/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:04:02 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/27 17:17:58 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void	printmap(t_map *map)
// {
// 	size_t	index;

// 	ft_printf("\n%c", map->previous_slot);
// 	index = 0;
// 	while (index < ft_strlen(map->data))
// 	{
// 		if (index % map->linelen == 0)
// 			ft_printf("\n");
// 		ft_printf("%c", map->data[index]);
// 		index++;
// 	}
// 	ft_printf("\n");
// }

void	up(t_map *map, int *i)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player - map->linelen) == '1')
		return ;
	(*i)++;
	if (!map->previous_slot || map->previous_slot == 'T')
		*player = 'F';
	else
		*player = map->previous_slot;
	map->previous_slot = *(player - map->linelen);
	*(player - map->linelen) = 'P';
	// printmap(map);
	ft_printf("%d\n", *i);
}

void	down(t_map *map, int *i)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player + map->linelen) == '1')
		return ;
	(*i)++;
	if (!map->previous_slot || map->previous_slot == 'T')
		*player = 'F';
	else
		*player = map->previous_slot;
	map->previous_slot = *(player + map->linelen);
	*(player + map->linelen) = 'P';
	// printmap(map);
	ft_printf("%d\n", *i);
}

void	right(t_map *map, int *i)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player + 1) == '1')
		return ;
	(*i)++;
	if (!map->previous_slot || map->previous_slot == 'T')
		*player = 'F';
	else
		*player = map->previous_slot;
	map->previous_slot = *(player + 1);
	*(player + 1) = 'P';
	// printmap(map);
	ft_printf("%d\n", *i);
}

void	left(t_map *map, int *i)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player - 1) == '1')
		return ;
	(*i)++;
	if (!map->previous_slot || map->previous_slot == 'T')
		*player = 'F';
	else
		*player = map->previous_slot;
	map->previous_slot = *(player - 1);
	*(player - 1) = 'P';
	// printmap(map);
	ft_printf("%d\n", *i);
}
