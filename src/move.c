/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 14:32:33 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int						get_pos(t_env *env, int x, int y)
{
	if (x <= env->map_x && y <= env->map_y)
		return (env->map[x][y]);
	return (-1);
}

void					move_player(t_env *env, double speed, double modifier)
{
	int			pos_x;
	int			pos_y;

	pos_x = env->pos_x + modifier * env->dir_x * speed;
	pos_y = env->pos_y + modifier * env->dir_y * speed;
	if (pos_x <= env->map_x && pos_y <= env->map_y)
	{
		if (get_pos(env, pos_x, pos_y) <= 0)
		{
			env->pos_x += env->dir_x * speed * modifier;
			env->pos_y += env->dir_y * speed * modifier;
			env->update = 1;
		}
	}
}

void					move_forward(t_env *env, double speed)
{
	move_player(env, speed, 1.0);
}

void					move_backward(t_env *env, double speed)
{
	move_player(env, speed, -1.0);
}

void					rotate_player(t_env *env, double speed)
{
	double		temp;

	temp = env->dir_x;
	env->dir_x = temp * cos(speed) - env->dir_y * sin(speed);
	env->dir_y = temp * sin(speed) + env->dir_y * cos(speed);
	temp = env->plane_x;
	env->plane_x = temp * cos(speed) - env->plane_y * sin(speed);
	env->plane_y = temp * sin(speed) + env->plane_y * cos(speed);
	env->update = 1;
	printf("dirX = %f, dirY = %f, planeX = %f, planeY = %f\n", env->dir_x,
		env->dir_y, env->plane_x, env->plane_y);
}
