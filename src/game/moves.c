/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:04:02 by tlamit            #+#    #+#             */
/*   Updated: 2026/01/28 14:02:14 by tlamit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_printf("%d\n", *i);
}
