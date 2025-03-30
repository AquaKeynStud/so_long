/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:45:44 by arocca            #+#    #+#             */
/*   Updated: 2025/03/21 15:12:12 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

int	close_window(t_data *data, int exit_code)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		free_map(data->map);
	exit(exit_code);
}

static bool	window_create(t_data *data, int	*mapw, int *maph)
{
	data->moves = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (false);
	mlx_get_screen_size(data->mlx, &data->winw, &data->winh);
	data->winw = (data->winw - (data->winw % SX));
	data->winh = (data->winh - (data->winh % SY));
	if (*mapw >= (data->winw / SX) || *maph >= (data->winh / SY))
	{
		free(data->mlx);
		free_map(data->map);
		return (false);
	}
	data->win = mlx_new_window(data->mlx, *mapw * SX, *maph * SY, "so_long");
	if (!data->win)
	{
		free(data->mlx);
		return (false);
	}
	return (true);
}

int	end_loop(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

static bool	verif_ext(char *file, char *ext)
{
	int		len;
	int		pad;

	len = ft_strlen(file);
	pad = ft_strlen(ext);
	if (len < pad)
		return (false);
	while (pad--)
	{
		if (file[len - pad] != ext[ft_strlen(ext) - pad])
			return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_images	images;
	t_map		*map;

	map = NULL;
	print_title();
	if (argc != 2 || !verif_ext(argv[1], ".ber"))
		return (ft_printf("Error\n"));
	if (!get_map(argv[1], &map, &data))
		return (1);
	if (!window_create(&data, &map->width, &map->height))
		return (ft_printf("Error\n"));
	if (!init_images(&data, &images))
		return (close_window(&data, EXIT_FAILURE));
	display_images(&data, images, map);
	mlx_hook(data.win, 17, 0, end_loop, &data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_loop(data.mlx);
	free_images(&data, &images);
	close_window(&data, EXIT_SUCCESS);
}
