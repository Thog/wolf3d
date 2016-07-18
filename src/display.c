/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:02:43 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 14:56:49 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "stdio.h"

int			init_display(t_env *env)
{
	if (!(env->mlx = mlx_init()) ||
			!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "wolf3d")) ||
			!(env->render = new_img(env->mlx, WIDTH, HEIGHT)))
		return (ft_error_retint("Display cannot be initialized!\n", 1));
	env->update = 1;
	ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	mlx_key_hook(env->win, key_hook, env);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	return (0);
}

void		perform_pixel(t_env *env, double *map, int side, double wall_dist)
{
	int			line_height;
	t_pos		*start;
	t_pos		*end;
	int			color;

	(void)side;
	wall_dist = fabs(wall_dist);
	line_height = (int)(HEIGHT / wall_dist);
	start = new_pos(env->temp_x, (HEIGHT - line_height) / 2, 0);
	end = new_pos(env->temp_x, (HEIGHT + line_height) / 2, 0);
	color = get_face_color(get_pos(env, (int)map[0], (int)map[1]));
	draw_line_2d(env->render, start, end, color);
	ft_memdel((void**)&start);
	ft_memdel((void**)&end);
}

void		perform_dda(t_env *env, double *data, double *side, double *dir)
{
	int		hit;
	int		visual_side;
	double	map[3];

	hit = 0;
	map[0] = (int)env->pos_x;
	map[1] = (int)env->pos_y;
	while (!hit)
	{
		visual_side = side[0] > side[1];
		side[visual_side] += data[visual_side];
		map[visual_side] += data[2 + visual_side];
		if (get_pos(env, (int)map[0], (int)map[1]) != 0)
			hit = 1;
	}
	map[2] = (!visual_side ? env->pos_x : env->pos_y);
	perform_pixel(env, map, visual_side, (map[visual_side] - map[2] +
		(1 - data[2 + visual_side]) / 2) / dir[visual_side]);
}

void		process_raycasting(t_env *env, int x, double *ray_dir)
{
	double		side[2];
	double		data[4];

	env->temp_x = x;
	data[0] = sqrt(1 + (ray_dir[1] * ray_dir[1]) / (ray_dir[0] * ray_dir[0]));
	data[1] = sqrt(1 + (ray_dir[0] * ray_dir[0]) / (ray_dir[1] * ray_dir[1]));
	data[2] = ray_dir[0] < 0 ? -1 : 1;
	data[3] = ray_dir[1] < 0 ? -1 : 1;
	side[0] = data[2] == -1 ? ((env->pos_x - (int)env->pos_x) * data[0]) :
		(((int)env->pos_x + 1.0 - env->pos_x) * data[0]);
	side[1] = data[3] == -1 ? ((env->pos_y - (int)env->pos_y) * data[1]) :
		(((int)env->pos_y + 1.0 - env->pos_y) * data[1]);
	perform_dda(env, data, side, ray_dir);
}

void		recompile_render(t_env *env)
{
	int			x;
	double		camera_x;
	double		ray_dir[2];

	x = -1;
	if (env->render && env->render->data)
		ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	while ((++x) < WIDTH)
	{
		camera_x = (2 * x) / (double)(WIDTH - 1);
		ray_dir[0] = env->dir_x + env->plane_x * camera_x;
		ray_dir[1] = env->dir_y + env->plane_y * camera_x;
		process_raycasting(env, x, ray_dir);
	}
}
