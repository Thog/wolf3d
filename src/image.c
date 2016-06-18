/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:56 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/07 13:45:41 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	init_img(t_image *img)
{
	int		line_size;
	int		bits;
	int		endian;

	img->data = mlx_get_data_addr(img->ptr, &bits, &line_size, &endian);
	img->byte_per_pixel = bits / 8;
	img->endian = endian;
	img->line_size = line_size;
}

t_image		*new_img(void *mlx, int width, int height)
{
	t_image *result;

	if ((result = (t_image*)ft_memalloc(sizeof(t_image))))
	{
		result->ptr = mlx_new_image(mlx, width, height);
		result->width = width;
		result->height = height;
		init_img(result);
		return (result);
	}
	return (NULL);
}

void		set_pixel(t_image *img, int x, int y, unsigned int color)
{
	int		pos;

	pos = (x * img->byte_per_pixel) + y * img->line_size;
	img->data[pos] = (color & 0xFF0000) >> 16;
	img->data[pos + 1] = (color & 0xFF00) >> 8;
	img->data[pos + 2] = color & 0xFF;
}
