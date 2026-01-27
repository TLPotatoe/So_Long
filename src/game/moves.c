/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:04:02 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/27 16:19:35 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	up(t_map *map)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player - map->linelen) != '1')
		return ;
	if (map->previous_slot)
		*player = map->previous_slot;
	map->previous_slot = *(player - map->linelen);
	*(player - map->linelen) = 'P';
}

void	down(t_map *map)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player + map->linelen) != '1')
		return ;
	if (map->previous_slot)
		*player = map->previous_slot;
	map->previous_slot = *(player + map->linelen);
	*(player + map->linelen) = 'P';
}

void	right(t_map *map)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player + 1) != '1')
		return ;
	if (map->previous_slot)
		*player = map->previous_slot;
	map->previous_slot = *(player + 1);
	*(player + 1) = 'P';
}

void	left(t_map *map)
{
	char	*player;

	player = ft_strchr(map->data, 'P');
	if (*(player - 1) != '1')
		return ;
	if (map->previous_slot)
		*player = map->previous_slot;
	map->previous_slot = *(player - 1);
	*(player - 1) = 'P';
}
