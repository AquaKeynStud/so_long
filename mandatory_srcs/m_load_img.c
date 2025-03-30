/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:57 by arocca            #+#    #+#             */
/*   Updated: 2025/03/21 14:28:01 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

void	free_images(t_data *data, t_images *img)
{
	mlx_destroy_image(data->mlx, img->wall);
	mlx_destroy_image(data->mlx, img->exit);
	mlx_destroy_image(data->mlx, img->floor);
	mlx_destroy_image(data->mlx, img->collec);
	mlx_destroy_image(data->mlx, img->player);
	data->images = NULL;
}

static bool	load_images(void *mlx, void **imgs, char **paths)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = SX;
	y = SY;
	while (i < 5)
	{
		imgs[i] = mlx_xpm_file_to_image(mlx, paths[i], &x, &y);
		if (!imgs[i])
		{
			ft_printf("Error\n");
			while (i--)
				mlx_destroy_image(mlx, imgs[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_images(t_data *data, t_images *img)
{
	char	*paths[5];
	void	*images[5];

	data->images = img;
	paths[0] = "./assets/wall1.xpm";
	paths[1] = "./assets/exit1.xpm";
	paths[2] = "./assets/floor1.xpm";
	paths[3] = "./assets/collectible1.xpm";
	paths[4] = "./assets/p_down.xpm";
	if (!load_images(data->mlx, images, paths))
		return (false);
	img->wall = images[0];
	img->exit = images[1];
	img->floor = images[2];
	img->collec = images[3];
	img->player = images[4];
	return (true);
}
