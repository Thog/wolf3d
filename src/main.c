/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:48 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/05 13:55:47 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		close_event(void *param)
{
	if (param)
		exit(destroy_env((t_env*)param, 0));
	return (param == NULL);
}

int		main(int ac, char **av)
{
	t_env		*env;

	if (ac != 2)
	{
		ft_printf("Usage: %s basic.wolf\n", *av);
		return (0);
	}
	ft_printf("wolf3d v%i.%i (%s %s)\n", VERSION_MAJOR, VERSION_MINOR, __DATE__,
		__TIME__);
	env = init_data(*(av + 1));
	if (!env || init_display(env))
		return (!env ? 1 : 2);
	mlx_loop(env->mlx);
	return (destroy_env(env, 0));
}
