/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:28 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/05 13:53:45 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int				alloc_data(t_env **env)
{
	return (!(*env = (t_env*)ft_memalloc(sizeof(t_env)))
			|| !((*env)->player = (t_player*)ft_memalloc(sizeof(t_player)))
			|| !((*env)->camera = (t_camera*)ft_memalloc(sizeof(t_camera)))
			|| !((*env)->draw = (t_draw*)ft_memalloc(sizeof(t_draw))));
}

int						is_valid_header(int fd)
{
	char		*header;
	int			result;

	header = read_fd(fd, 10);
	if (!header)
		return (ft_error_retint("Cannot read header of file\n", 1));
	result = !ft_memcmp(header, "WOLF3D\0\0\0", 10);
	ft_memdel((void**)&header);
	return (result);
}

int						parse_header(t_env *env, int fd)
{
	unsigned short	total_map_bytes;

	if (!is_valid_header(fd) || !read8(fd, &env->map_x)
			|| !read8(fd, &env->map_y) || !read16(fd, &env->block_size)
			|| !read16(fd, &total_map_bytes))
		return (ft_error_retint("Invalid file!\n", 1));
	env->player->pos_x = 7.0;
	env->player->pos_y = 7.0;
	return ((total_map_bytes != (env->map_x * env->map_y)) ?
			ft_error_retint("Invalid map sum\n", 1) : 0);
}

int						parse_map(t_env *env, int fd)
{
	int				x;
	int				y;
	unsigned char	test;

	if (!(env->map = (unsigned char**)ft_memalloc(
					sizeof(char*) * (env->map_y + 1))))
		return (ft_error_retint("Map allocation failed!\n", 1));
	y = -1;
	while ((++y) < (env->map_y + 1))
	{
		if (!(env->map[y] = (unsigned char*)ft_memalloc(sizeof(char)
						* (env->map_x + 1))))
			return (ft_error_retint("Map line allocation failed!\n", 1));
		x = -1;
		while ((++x) < (env->map_x + 1))
		{
			if (!read8(fd, &test))
				return (ft_error_retint("Map is incorrect!\n", 1));
			env->map[y][x] = test;
			ft_printf((env->player->pos_x == x && env->player->pos_y == y ?
						"X|" : "%d|"), env->map[y][x]);
		}
		ft_printf("\n");
	}
	return (0);
}

t_env					*init_data(char *file)
{
	int					fd;
	int					error;
	t_env				*env;

	error = 0;
	fd = open(file, O_RDONLY);
	if (alloc_data(&env))
		error = ft_error_retint("Cannot allocate memory for env struct!\n", 1);
	if (fd == -1)
		error = ft_error_retint("File not found\n", 1);
	if (!error)
	{
		if (!(error = parse_header(env, fd)))
			ft_printf("xSize: %u, ySize: %u, blockSize: %u\n", env->map_x + 1,
					env->map_y + 1, env->block_size);
		env->player->dir_x = DIR_X;
		env->player->dir_y = DIR_Y;
		env->player->speed_move = SPEED_MOVE;
		env->player->speed_rotate = SPEED_ROTATE;
		env->camera->plane_x = CAM_X;
		env->camera->plane_y = CAM_Y;
		error = error ? error : parse_map(env, fd);
	}
	close(fd);
	return (error ? NULL : env);
}
