/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/28 16:11:11 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int						get_pos(t_env *env, int x, int y)
{
	if (x < env->map_x && y < env->map_y)
		return (env->map[x][y]);
	ft_printf("OutOfMapException: %d, %d\n", x, y);
	exit(0);
	return (0);
}

void					move_forward(t_env *env)
{
	(void)env;
}

void					move_backward(t_env *env)
{
	(void)env;
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
