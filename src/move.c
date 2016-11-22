/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 18:36:56 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void					rotate_player_right(t_env *e)
{
	double		old_dir;
	double		old_plane;


	old_dir = e->player->dir_x;
	old_plane = e->camera->plane_x;
	e->player->dir_x = e->player->dir_x * cos(-e->player->speed_rotate)
		- e->player->dir_y * sin(-e->player->speed_rotate);
	e->player->dir_y = old_dir * sin(-e->player->speed_rotate)
		+ e->player->dir_y * cos(-e->player->speed_rotate);
	e->camera->plane_x = e->camera->plane_x * cos(-e->player->speed_rotate)
		- e->camera->plane_y * sin(-e->player->speed_rotate);
	e->camera->plane_y = old_plane * sin(-e->player->speed_rotate)
		+ e->camera->plane_y * cos(-e->player->speed_rotate);
	e->update = 1;
}

void					rotate_player_left(t_env *e)
{

	double		old_dir;
	double		old_plane;

	old_dir = e->player->dir_x;
	old_plane = e->camera->plane_x;
	e->player->dir_x = e->player->dir_x * cos(e->player->speed_rotate)
		- e->player->dir_y * sin(e->player->speed_rotate);
	e->player->dir_y = old_dir * sin(e->player->speed_rotate)
		+ e->player->dir_y * cos(e->player->speed_rotate);
	e->camera->plane_x = e->camera->plane_x * cos(e->player->speed_rotate)
		- e->camera->plane_y * sin(e->player->speed_rotate);
	e->camera->plane_y = old_plane * sin(e->player->speed_rotate)
		+ e->camera->plane_y * cos(e->player->speed_rotate);
	e->update = 1;
}

void					move_player_down(t_env *e)
{
	if (e->map[(int)(e->player->pos_x - e->player->dir_x
				* e->player->speed_move)][(int)e->player->pos_y] == 0)
		e->player->pos_x -= e->player->dir_x * e->player->speed_move;
	if (e->map[(int)e->player->pos_x][(int)(e->player->pos_y - e->player->dir_y
				* e->player->speed_move)] == 0)
		e->player->pos_y -= e->player->dir_y * e->player->speed_move;
	e->update = 1;
}

void					move_player_up(t_env *e)
{
	if (e->map[(int)(e->player->pos_x + e->player->dir_x
				* e->player->speed_move)][(int)(e->player->pos_y)] == 0)
		e->player->pos_x += e->player->dir_x * e->player->speed_move;
	if (e->map[(int)(e->player->pos_x)][(int)(e->player->pos_y + e->player->dir_y
				* e->player->speed_move)] == 0)
		e->player->pos_y += e->player->dir_y * e->player->speed_move;
	e->update = 1;
}

void					render_infos(t_env *env)
{
	char			*tmp;

	mlx_string_put(env->mlx, env->win, 10, 10, 0xFFF00F, "Position");
	tmp = ft_itoa_prefix("X: ", (int)env->player->pos_x);
	mlx_string_put(env->mlx, env->win, 10, 50, 0xFFF00F, tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa_prefix("Y: ", (int)env->player->pos_y);
	mlx_string_put(env->mlx, env->win, 10, 90, 0xFFF00F, tmp);
	ft_strdel(&tmp);
}
