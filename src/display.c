/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:02:43 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 18:37:16 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "stdio.h"

int			get_pos(t_env *env, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= env->map_x && y <= env->map_y)
		return (env->map[x][y]);
	return (-1);
}

int			init_display(t_env *env)
{
	if (!(env->mlx = mlx_init()) ||
			!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "wolf3d")) ||
			!(env->render = new_img(env->mlx, WIDTH, HEIGHT)))
		return (ft_error_retint("Display cannot be initialized!\n", 1));
	env->update = 1;
	ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_press, env);
	mlx_hook(env->win, KEYRELEASE, KEYRELEASEMASK, key_release, env);
	mlx_hook(env->win, CLOSE, CLOSEMASK, close_event, env);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	return (0);
}

static void	setup_pass(t_env *e)
{
	e->camera->x = 2 * e->draw->x / (double)WIDTH - 1;
	e->draw->side = 0;
	e->draw->hit = 0;
	e->camera->pos_x = e->player->pos_x;
	e->camera->pos_y = e->player->pos_y;
	e->camera->dir_x = e->player->dir_x + e->camera->plane_x * e->camera->x;
	e->camera->dir_y = e->player->dir_y + e->camera->plane_y * e->camera->x;
	e->draw->map_x = (int)e->camera->pos_x;
	e->draw->map_y = (int)e->camera->pos_y;
	e->draw->dist_delta_x = sqrt(1 + pow(e->camera->dir_y, 2)
								/ pow(e->camera->dir_x, 2));
	e->draw->dist_delta_y = sqrt(1 + pow(e->camera->dir_x, 2)
								/ pow(e->camera->dir_y, 2));
}

static void	draw_column(t_env *e)
{
	unsigned int	color;
	int				y;

	y = -1;
	while ((++y) < HEIGHT)
	{
		if (y < e->draw->start)
			color = CYAN;
		else if (y > e->draw->end)
			color = GREEN;
		else
			color = get_face_color(e);
		set_pixel(e->render, e->draw->x, y, color);
	}
}

void		recompile_render(t_env *env)
{
	env->draw->x = 0;
	if (env->render && env->render->data)
		ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	while (env->draw->x < WIDTH)
	{
		setup_pass(env);
		process_raycasting(env);
		draw_column(env);
		env->draw->x++;
	}
}
