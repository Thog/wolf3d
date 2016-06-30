/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:02:43 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/28 17:50:30 by tguillem         ###   ########.fr       */
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
	//mlx_mouse_hook(env->win, mouse_hook, env);
	//mlx_hook(env->win, 6, (1L << 6), motion_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	return (0);
}

void		perform_pixel(t_env *env, double *map, double side, double wall_dist)
{
	int			line_height;
	t_pos		*start;
	t_pos		*end;
	int			color;

	line_height = (int)(HEIGHT / wall_dist);
	start = new_pos(env->temp_x, (HEIGHT - line_height) / 2, 0);
	end = new_pos(env->temp_x, (HEIGHT + line_height) / 2, 0);
	color = get_face_color(get_pos(env, (int)map[0], (int)map[1]) / (2 * side));
	//color = !side ? color / 2 : color;
	draw_line_2d(env->render, start, end, color);
	ft_memdel((void**)&start);
	ft_memdel((void**)&end);
}

void		perform_dda(t_env *env, double *delta, int *step, double *side, double *dir)
{
	int		hit;
	int		visual_side;
	double	map[3];

	hit = 0;
	map[0] = (int)env->pos_x;
	map[1] = (int)env->pos_y;
	printf("Map position: %f, %f\n==================\n", map[0], map[1]);
	while (!hit)
	{
		visual_side = side[0] > side[1];
		side[visual_side] += delta[visual_side];
		map[visual_side] += step[visual_side];
		if (get_pos(env, (int)map[0], (int)map[1]) != 0)
			hit = 1;
	}
	map[2] = (int)(!visual_side ? env->pos_x : env->pos_y);
	printf("Map position: %f, %f\nSide: %f\nDelta: %f\n", map[0], map[1], side[visual_side], delta[visual_side]);
	perform_pixel(env, map, visual_side, ((map[visual_side] - map[2] +
		(1 - step[visual_side])) / 2) / dir[visual_side]);
}

void		process_raycasting(t_env *env, int x, double *ray_dir)
{
	double		delta[2];
	int			step[2];
	double		side[2];

	env->temp_x = x;
	delta[0] = sqrt(1 + (ray_dir[1] * ray_dir[1]) / (ray_dir[0] * ray_dir[0]));
	delta[1] = sqrt(1 + (ray_dir[0] * ray_dir[0]) / (ray_dir[1] * ray_dir[1]));
	step[0] = ray_dir[0] < 0 ? -1 : 1;
	step[1] = ray_dir[1] < 0 ? -1 : 1;
	side[0] = step[0] == -1 ? ((env->pos_x - (int)env->pos_x) * delta[0]) :
		(((int)env->pos_x + 1.0 - env->pos_x) * delta[0]);
	side[1] = step[1] == -1 ? ((env->pos_y - (int)env->pos_y) * delta[1]) :
		(((int)env->pos_y + 1.0 - env->pos_y) * delta[1]);
	printf("sideX = %f\n", ((env->pos_x + 1 - env->pos_x)) * delta[0]);
	printf("sideX = %f\nsideY = %f\ndeltaX = %f\ndeltaY = %f\n", side[0], side[1], delta[0], delta[1]);
	perform_dda(env, delta, step, side, ray_dir);
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
		printf("cameraX = %f\nrayX = %f\nrayY = %f\n", camera_x, ray_dir[0], ray_dir[1]);
		process_raycasting(env, x, ray_dir);
	}
}
