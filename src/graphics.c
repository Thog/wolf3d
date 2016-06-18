/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:59 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/07 13:55:30 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				draw_line1(int nbr[2], int error[2], t_pos *p2, int n)
{
	if ((error[0] << 1) >= n)
	{
		nbr[0] += (p2->x - nbr[0]) >= 0 ? 1 : -1;
		error[0] -= n;
	}
	if ((error[1] << 1) >= n)
	{
		nbr[1] += (p2->y - nbr[1]) >= 0 ? 1 : -1;
		error[1] -= n;
	}
}

int					put_pixel(t_image *img, int x, int y, unsigned int color)
{
	if (!img || x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	set_pixel(img, x, y, color);
	return (1);
}

int					draw_line_2d(t_image *img, t_pos *p1, t_pos *p2,
	t_colorizer *colorizer)
{
	int i;
	int n;
	int nbr[3];
	int error[2];
	int delta[2];

	(void)colorizer;
	i = -1;
	nbr[0] = p1->x;
	nbr[1] = p1->y;
	nbr[2] = 0;
	delta[0] = (p2->x - p1->x) < 0 ? -(p2->x - p1->x) : (p2->x - p1->x);
	delta[1] = (p2->y - p1->y) < 0 ? -(p2->y - p1->y) : (p2->y - p1->y);
	n = delta[0] > delta[1] ? delta[0] : delta[1];
	ft_bzero(error, sizeof(error));
	while (++i < n)
	{
		nbr[2] += put_pixel(img, nbr[0], nbr[1], (*colorizer)(i));
		error[0] += delta[0];
		error[1] += delta[1];
		draw_line1(nbr, error, p2, n);
	}
	return (nbr[2]);
}

int					draw_line_3d(t_image *img, t_pos *start, t_pos *end,
	t_colorizer *colorizer)
{
	int		result;
	t_pos	*tmp1;
	t_pos	*tmp2;

	result = 1;
	if (!start || !end)
		return (result);
	tmp1 = new_pos(PROJ_ISO_X(start->x, start->y, start->z),
		PROJ_ISO_Y(start->x, start->y, start->z), start->z);
	tmp2 = new_pos(PROJ_ISO_X(end->x, end->y, end->z),
		PROJ_ISO_Y(end->x, end->y, end->z), end->z);
	result = draw_line_2d(img, tmp1, tmp2, colorizer);
	put_pixel(img, tmp1->x, tmp1->y, (*colorizer)(0));
	put_pixel(img, tmp2->x, tmp2->y, (*colorizer)(0));
	ft_memdel((void**)&tmp1);
	ft_memdel((void**)&tmp2);
	return (result);
}
