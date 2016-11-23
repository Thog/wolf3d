/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:48 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 17:54:24 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		close_event(void *param)
{
	if (param)
		exit(destroy_env((t_env*)param, 0));
	return (param == NULL);
}

int		main(void)
{
	t_env		*env;

	ft_printf("wolf3d v%i.%i (%s %s)\n", VERSION_MAJOR, VERSION_MINOR, __DATE__,
		__TIME__);
	env = init_data();
	if (!env || init_display(env))
		return (!env ? 1 : 2);
	mlx_loop(env->mlx);
	return (destroy_env(env, 0));
}
