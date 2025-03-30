/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:44:59 by arocca            #+#    #+#             */
/*   Updated: 2025/03/21 13:48:24 by arocca           ###   ########.fr       */
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

bool	has_unverified_neighbor(t_map *dmap, int y, int x)
{
	t_case	**map;
	int		height;
	int		width;

	map = dmap -> map;
	height = dmap -> height;
	width = dmap -> width;
	if (y + 1 < height && map[y + 1][x].type != '1' && !map[y + 1][x].verified)
		return (true);
	if (y - 1 >= 0 && map[y - 1][x].type != '1' && !map[y - 1][x].verified)
		return (true);
	if (x + 1 < width && map[y][x + 1].type != '1' && !map[y][x + 1].verified)
		return (true);
	if (x - 1 >= 0 && map[y][x - 1].type != '1' && !map[y][x - 1].verified)
		return (true);
	return (false);
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
		if (q->rear < q->size && has_unverified_neighbor(map, y, x))
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
