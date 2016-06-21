#include "wolf3d.h"

int				key_hook(int keycode, void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		if (keycode == ESCAPE)
			exit(destroy_env(env, 0));
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
	}
	return (param == NULL);
}

int				loop_hook(void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		if (env->update)
		{
			recompile_render(env);
			expose_hook(param);
			env->update = 0;
		}
	}
	return (param == NULL);
}
