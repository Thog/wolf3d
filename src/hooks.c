/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:02:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 17:02:20 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			key_update(t_env *env)
{
	if (env->key_up)
		move_player_up(env);
	if (env->key_left)
		rotate_player_left(env);
	if (env->key_right)
		rotate_player_right(env);
	if (env->key_down)
		move_player_down(env);
}

int				key_press(int keycode, void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		if (keycode == ESCAPE)
			exit(destroy_env(env, 0));
		else if (keycode == ARROW_UP)
			env->key_up = 1;
		else if (keycode == ARROW_LEFT)
			env->key_left = 1;
		else if (keycode == ARROW_RIGHT)
			env->key_right = 1;
		else if (keycode == ARROW_DOWN)
			env->key_down = 1;
		else
			ft_printf("Keycode: %d\n", keycode);
	}
	return (param == NULL);
}

int				key_release(int keycode, void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		if (keycode == ARROW_UP)
			env->key_up = 0;
		else if (keycode == ARROW_LEFT)
			env->key_left = 0;
		else if (keycode == ARROW_RIGHT)
			env->key_right = 0;
		else if (keycode == ARROW_DOWN)
			env->key_down = 0;
		else
			ft_printf("Keycode: %d\n", keycode);
	}
	return (param == NULL);
}

int				expose_hook(void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		mlx_put_image_to_window(env->mlx, env->win, env->render->ptr, 0, 0);
		render_infos(env);
	}
	return (param == NULL);
}

int				loop_hook(void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		key_update(env);
		if (env->update)
		{
			recompile_render(env);
			expose_hook(param);
			env->update = 0;
		}
	}
	return (param == NULL);
}
