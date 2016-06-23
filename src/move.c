#include "wolf3d.h"

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
}
