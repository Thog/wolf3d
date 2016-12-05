/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:45:43 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/05 13:45:45 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	perform_step(t_env *e)
{
	if (e->camera->dir_x < 0)
	{
		e->draw->step_x = -1;
		e->draw->dist_side_x = (e->camera->pos_x - (double)e->draw->map_x)
			* e->draw->dist_delta_x;
	}
	else
	{
		e->draw->step_x = 1;
		e->draw->dist_side_x = ((double)e->draw->map_x + 1.0 - e->camera->pos_x)
			* e->draw->dist_delta_x;
	}
	if (e->camera->dir_y < 0)
	{
		e->draw->step_y = -1;
		e->draw->dist_side_y = (e->camera->pos_y - (double)e->draw->map_y)
			* e->draw->dist_delta_y;
	}
	else
	{
		e->draw->step_y = 1;
		e->draw->dist_side_y = ((double)e->draw->map_y + 1.0 - e->camera->pos_y)
			* e->draw->dist_delta_y;
	}
}

static void	perform_dda(t_env *e)
{
	while (e->draw->hit == 0)
	{
		if (e->draw->dist_side_x < e->draw->dist_side_y)
		{
			e->draw->dist_side_x += e->draw->dist_delta_x;
			e->draw->map_x += e->draw->step_x;
			e->draw->side = 0;
		}
		else
		{
			e->draw->dist_side_y += e->draw->dist_delta_y;
			e->draw->map_y += e->draw->step_y;
			e->draw->side = 1;
		}
		if (get_pos(e, e->draw->map_x, e->draw->map_y) != 0)
			e->draw->hit = 1;
	}
}

static void	compute_distance(t_env *e)
{
	if (e->draw->side == 0)
		e->camera->dist_wall = fabs((e->draw->map_x - e->camera->pos_x
					+ (1 - e->draw->step_x) / 2)
				/ e->camera->dir_x);
	else
		e->camera->dist_wall = fabs((e->draw->map_y - e->camera->pos_y
					+ (1 - e->draw->step_y) / 2)
				/ e->camera->dir_y);
	if (e->camera->dist_wall <= 0.005)
		e->camera->dist_wall = 0.005;
	e->draw->height = ABS((int)(HEIGHT / e->camera->dist_wall));
	e->draw->start = (-e->draw->height / 2) + HEIGHT / 2;
	if (e->draw->start < 0)
		e->draw->start = 0;
	e->draw->end = e->draw->height / 2 + HEIGHT / 2;
	if (e->draw->end >= HEIGHT)
		e->draw->end = HEIGHT;
}

static void	compute_height(t_env *e)
{
	e->draw->height = fabs(HEIGHT / e->camera->dist_wall);
	if ((e->draw->start = -e->draw->height / 2 + HEIGHT / 2) < 0)
		e->draw->start = 0;
	if ((e->draw->end = e->draw->height / 2 + HEIGHT / 2) >= HEIGHT)
		e->draw->end = HEIGHT - 1;
}

void		process_raycasting(t_env *env)
{
	perform_step(env);
	perform_dda(env);
	compute_distance(env);
	compute_height(env);
}
