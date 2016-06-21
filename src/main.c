#include "wolf3d.h"

int		main(void)
{
	t_env		*env;

	ft_printf("wolf3d v%i.%i (%s %s)\n", VERSION_MAJOR, VERSION_MINOR, __DATE__, __TIME__);
	env = init_data();
	if (!env)
		return (1);
	return (destroy_env(env, 0));
}
