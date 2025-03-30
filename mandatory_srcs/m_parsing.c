/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:55:15 by arocca            #+#    #+#             */
/*   Updated: 2025/03/24 18:01:00 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

static bool	isnt_wall_surrounded(t_map *map, int width, int height)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0].type != '1' || map->map[i][width].type != '1')
			return (ft_printf("Error\n"));
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i].type != '1' || map->map[height][i].type != '1')
			return (ft_printf("Error\n"));
		i++;
	}
	return (false);
}

static bool	forbidden_type(t_case cell)
{
	return (type_of(cell) < 0);
}

static bool	double_player(t_case cell)
{
	return (cell.type == 'P');
}

static bool	double_exit(t_case cell)
{
	return (cell.type == 'E');
}

int	err_map_parsing(t_map *map, t_data *data)
{
	if ((map->width == 0 && map->height == 0))
		return (ft_printf("Error\n"));
	if (isnt_wall_surrounded(map, map->width - 1, map->height - 1))
		return (1);
	if (browse_map(map, forbidden_type) || browse_map(map, double_player) != 1
		|| browse_map(map, double_exit) != 1 || map->items == 0)
		return (ft_printf("Error\n"));
	bfs(map, data->pyx[1], data->pyx[0]);
	if (browse_map(map, is_item_unreachable))
		return (1);
	return (0);
}
