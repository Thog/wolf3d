#include "wolf3d.h"

int		main(void)
{
	t_env		*env;

	env = init_data();
	if (!env)
		return (1);
	return (destroy_env(env, 0));
}
