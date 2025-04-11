/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_bfs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:44:59 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 15:56:58 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

t_queue	*queue_init(t_map *map, int start_x, int start_y)
{
	t_queue	*q;

	q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->q = malloc(sizeof(t_case *) * (map->width * map->height));
	if (!q->q)
		return (free(q), NULL);
	q->front = 0;
	q->rear = 0;
	q->size = map->width * map->height;
	q->q[q->rear++] = &map->map[start_y][start_x];
	map->map[start_y][start_x].verified = true;
	return (q);
}

void	handle_direction(t_map *map, t_queue *q, t_case *c, int direction)
{
	int	x;
	int	y;

	x = c->x;
	y = c->y;
	if (direction == 0)
		x--;
	else if (direction == 1)
		y++;
	else if (direction == 2)
		x++;
	else
		y--;
	if (x < 0 || y < 0 || y >= map -> height || x >= map -> width)
		return ;
	if (!map->map[y][x].verified && map->map[y][x].type != '1')
	{
		map->map[y][x].verified = true;
		if (q->rear < q->size)
			q->q[q->rear++] = &map->map[y][x];
	}
}

void	bfs(t_map *map, int start_x, int start_y)
{
	t_queue	*queue;
	t_case	*cell;
	int		i;

	queue = queue_init(map, start_x, start_y);
	if (!queue)
		return ;
	while (queue->front != queue->rear)
	{
		cell = queue->q[queue->front++];
		i = 0;
		while (i < 4)
		{
			handle_direction(map, queue, cell, i);
			i++;
		}
	}
	free(queue->q);
	free(queue);
}

bool	is_item_unreachable(t_case cell)
{
	if (cell.verified == true || cell.type == '1' || cell.type == '0')
		return (false);
	if (cell.type == 'P' || cell.type == 'C' || cell.type == 'E')
		ft_printf("Error\n");
	return (true);
}

bool	err_stuck_by_exit(t_map *dmap)
{
	int		i;
	int		j;
	t_case	**map;

	i = 0;
	map = dmap -> map;
	while (i < dmap->height)
	{
		j = 0;
		while (j < dmap->width)
		{
			if (map[i][j].type == 'C' || map[i][j].type == 'P')
			{
				if (is_wall(map[i + 1][j]) && is_wall(map[i - 1][j])
					&& is_wall(map[i][j + 1]) && is_wall(map[i][j - 1]))
					return (ft_printf("Error\n"));
			}
			j++;
		}
		i++;
	}
	return (false);
}
