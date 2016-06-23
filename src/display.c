#include "wolf3d.h"

int			init_display(t_env *env)
{
	if (!(env->mlx = mlx_init()) ||
			!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "wolf3d")))
		return (1);
	env->update = 1;
	env->render = new_img(env->mlx, WIDTH, HEIGHT);
	ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	mlx_key_hook(env->win, key_hook, env);
	mlx_expose_hook(env->win, expose_hook, env);
	//mlx_mouse_hook(env->win, mouse_hook, env);
	//mlx_hook(env->win, 6, (1L << 6), motion_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	return (0);
}

void		perform_pixel(t_env *env, int *map, double side, double wall_dist)
{
	int			line_height;
	t_pos		*start;
	t_pos		*end;
	int			color;

	line_height = (int)(HEIGHT / wall_dist);
	start = new_pos(env->temp_x, (HEIGHT - line_height) / 2, 0);
	start->y = start->y < 0 ? 0 : start->y;
	end = new_pos(env->temp_x, (HEIGHT + line_height) / 2, 0);
	end->y = end->y >= HEIGHT ? HEIGHT - 1 : end->y;
	color = get_face_color(env->map[map[0]][map[1]]) / (2 * side);
	draw_line_2d(env->render, start, end, color);
	ft_memdel((void**)&start);
	ft_memdel((void**)&end);
}

void		perform_dda(t_env *env, double *delta, int *step, double *side, double *dir)
{
	int		hit;
	int		visual_side;
	int		map[2];

	hit = 0;
	map[0] = (int)env->pos_x;
	map[1] = (int)env->pos_y;

	while(!hit)
	{
		if (side[0] < side[1])
		{
			side[0] += delta[0];
			map[0] += step[0];
			visual_side = 0;
		}
		else
		{
			side[1] += delta[1];
			map[1] += step[1];
			visual_side = 1;
		}
		if (env->map[map[0]][map[1]] > 0) hit = 1;
	}
	perform_pixel(env, map, visual_side, (map[visual_side] - dir[visual_side] + (1 - step[visual_side])) / 2);
}

void 		process_raycasting(t_env *env, int x, double *dir)
{
	double		delta[2];
	int			step[2];
	double		side[2];

	env->temp_x =  x;
	delta[0] = sqrt(1 + (dir[1] * dir[1]) / (dir[0] * dir[0]));
	delta[0] = sqrt(1 + (dir[0] * dir[0]) / (dir[1] * dir[1]));
	step[0] = dir[0] < 0 ? -1 : 1;
	step[1] = dir[1] < 0 ? -1 : 1;
	side[0] = step[0] == -1 ? ((env->pos_x - (int)env->pos_x) * delta[0]) :
		(((int)env->pos_x + 1.0 - env->pos_x) * delta[0]);
	side[1] = step[1] == -1 ? ((env->pos_y - (int)env->pos_y) * delta[1]) :
		(((int)env->pos_y + 1.0 - env->pos_y) * delta[1]);
	perform_dda(env, delta, step, side, dir);
}

void		recompile_render(t_env *env)
{
	int			x;
	double		camera_x;
	double		dir[2];

	x = -1;
	if (env->render && env->render->data)
		ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	while ((++x) < WIDTH)
	{
		camera_x = (2 * x) / (double)(WIDTH - 1);
		dir[0] = env->dir_x + env->plane_x * camera_x;
		dir[1] = env->dir_y + env->plane_y * camera_x;
		process_raycasting(env, x, dir);
	}
}
